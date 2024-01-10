#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::gfx::vulkan;

struct Vertex { Vec3f pos, color; };
struct Handles { u32 cameraHandle, transformHandle; };
struct CameraTransform { Mat4f view, proj; };
struct Transform { Mat4f transform, scale, rotation; };

const std::vector<Vertex> vertices = {
    {{-1.0, -1.0, -1.0}, {0.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0, -1.0}, {0.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0, -1.0}, {0.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0, -1.0}, {0.0f, 0.0f, 0.0f}},
    {{-1.0, -1.0,  1.0}, {1.0f, 1.0f, 1.0f}},
    {{ 1.0, -1.0,  1.0}, {1.0f, 1.0f, 0.0f}},
    {{ 1.0,  1.0,  1.0}, {1.0f, 0.0f, 1.0f}},
    {{-1.0,  1.0,  1.0}, {1.0f, 0.0f, 0.0f}},
};

// Todo make this nicer
const auto vertexDescriptions = VulkanPipelineVertexInputStateTuple {
    .bindingDescriptions = {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attributeDescriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) },
    }
};

const std::vector<int> indices = {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

// Todo move view matrix to omni_types
Mat4f get_view_matrix(Vec3f position, Vec3f direction, Vec3f up);

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("2. Vulkan 3d cube example", 800, 600, GfxAPI::VULKAN);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swapChain = device->create_swap_chain(window);

    auto descriptorPool = device->create_descriptor_pool();
    auto descriptorSetLayout = device->create_descriptor_set_layouts({
        VulkanDescriptorSetLayoutBinding::bindless_uniform(0),
        VulkanDescriptorSetLayoutBinding::bindless_uniform(1)
    });
    auto descriptors = descriptorPool->create_descriptors(device, descriptorSetLayout[0], 3);

    auto pipelineLayout = device->create_pipeline_layout(descriptorSetLayout, {
        VulkanConstRange::common(sizeof(Handles), 0)
    });
    auto vertShaderModule = device->create_shader_module("vert.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragShaderModule = device->create_shader_module("frag.glsl", ShaderTypes::FRAGMENT_SHADER);
    auto pipeline = device->create_pipeline(swapChain, pipelineLayout, { vertShaderModule, fragShaderModule }, {
        .pVertexInputState = { .vertexDescriptions = vertexDescriptions }
    });

    auto vertexBuffer = device->create_buffer_memory(sizeof(Vertex) * vertices.size());
    auto indexBuffer = device->create_buffer_memory(sizeof(u32) * indices.size());
    vertexBuffer.memory->upload_data(device, vertices.data(), sizeof(Vertex) * vertices.size());
    indexBuffer.memory->upload_data(device, indices.data(), sizeof(u32) * indices.size());

    auto transformUBO = device->create_buffer_memorys(sizeof(Transform), 3); // Todo
    auto cameraUBO = device->create_buffer_memorys(sizeof(CameraTransform), 3);
    descriptorPool->update_descriptor_sets(device, transformUBO, sizeof(Transform), descriptors, 0, {0, 1, 2});
    descriptorPool->update_descriptor_sets(device, cameraUBO, sizeof(CameraTransform), descriptors, 1, {3, 4, 5});

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool->create_command_buffers(device, 3);

    auto cameraTransform = CameraTransform {
        get_view_matrix(Vec3f(0.0f, 0.0f, 10.0f), Vec3f::back, Vec3f::down),
        Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f)
    };

    auto transform = Transform {
        Mat4f::translation(Vec3f::zero),
        Mat4f::scale(1.0f),
        Mat4f::identity()
    };

    f32 t = 0.0f;

    while (!window->closing()) {
        ++t;

        GLFWContext::pool_events();

        uint32_t frame;
        auto result = swapChain->acquire_next_image(device, &frame);

        if(!result.is_ok())
            continue;

        transform.rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, t * 0.001f, 0.0f));
        cameraTransform.proj = Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f);

        transformUBO[frame].memory->upload_data(device, &transform, sizeof(Transform));
        cameraUBO[frame].memory->upload_data(device, &cameraTransform, sizeof(CameraTransform));

        auto handles = Handles {static_cast<u32>(frame + 3), static_cast<u32>(frame) };

        auto& cmd = commandBuffers[frame];

        cmd->begin_record()
            .begin_render_pass(swapChain, frame)
            .set_viewport(0, 0, window->get_width(), window->get_height())
            .bind_pipeline(pipeline)
            .bind_descriptor_set(pipelineLayout, descriptors, frame)
            .bind_vertex_buffer(vertexBuffer.buffer)
            .bind_index_buffer(indexBuffer.buffer)
            .push_constant(pipelineLayout, sizeof(Handles), 0, &handles)
            .draw_indexed(indices.size())
            .end_render_pass()
            .end_record();

        result = swapChain->submit_command_buffers(device, cmd, &frame);

        if(!result.is_ok()) // Todo check if window is resized
            continue;
    }

    device->wait_idle();

    device->destroy_all(commandBuffers);
    device->destroy_all(vertexBuffer.buffer, indexBuffer.buffer, vertexBuffer.memory, indexBuffer.memory,commandBufferPool);

    for(auto& b : transformUBO)
        device->destroy_all(b.buffer, b.memory);

    for(auto& b : cameraUBO)
        device->destroy_all(b.buffer, b.memory);

    device->destroy_all(descriptorSetLayout);
    device->destroy_all(descriptors);
    device->destroy_all(descriptorPool, vertShaderModule,fragShaderModule,pipelineLayout,pipeline, swapChain);

    device->destroy();
    instance->destroy();

    // Todo move all glfw things to glfw context static class
    GLFWContext::terminate();

    return 0;
}

Mat4f get_view_matrix(Vec3f position, Vec3f direction, Vec3f up) {
    const auto w = direction.normalize();
    const auto u = w.cross(up).normalize();
    const auto v = w.cross(u);

    auto viewMatrix = Mat4f::identity();
    viewMatrix[0 * 4 + 0] = u.x;
    viewMatrix[1 * 4 + 0] = u.y;
    viewMatrix[2 * 4 + 0] = u.z;
    viewMatrix[0 * 4 + 1] = v.x;
    viewMatrix[1 * 4 + 1] = v.y;
    viewMatrix[2 * 4 + 1] = v.z;
    viewMatrix[0 * 4 + 2] = w.x;
    viewMatrix[1 * 4 + 2] = w.y;
    viewMatrix[2 * 4 + 2] = w.z;
    viewMatrix[3 * 4 + 0] = -1.0f * (u).dot(position);
    viewMatrix[3 * 4 + 1] = -1.0f * (v).dot(position);
    viewMatrix[3 * 4 + 2] = -1.0f * (w).dot(position);

    return viewMatrix;
}
