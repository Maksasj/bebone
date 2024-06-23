#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
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

    auto [ vbuffer, vmemory ] = device->create_buffer_memory_from(vertices);
    auto [ ibuffer, imemory ] = device->create_buffer_memory_from(indices);

    auto transformUBO = device->create_buffer_memorys(sizeof(Transform), 3); // Todo
    auto cameraUBO = device->create_buffer_memorys(sizeof(CameraTransform), 3);
    descriptorPool->update_descriptor_sets(device, transformUBO, sizeof(Transform), descriptors, 0, {0, 1, 2}); // Todo, this thing is inlined
    descriptorPool->update_descriptor_sets(device, cameraUBO, sizeof(CameraTransform), descriptors, 1, {3, 4, 5}); // Todo, this thing is inlined

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool->create_command_buffers(device, 3);

    auto cameraTransform = CameraTransform {
        Mat4f::view(Vec3f(0.0f, 0.0f, 10.0f), Vec3f::back, Vec3f::down),
        Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f)
    };

    auto transform = Transform {
        Mat4f::translation(Vec3f::zero),
        Mat4f::scale(1.0f),
        Mat4f::identity()
    };

    f32 t = 0.0f;
    while (!window->closing()) {
        GLFWContext::poll_events();

        uint32_t frame;
        if(!swapChain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto& [_0, tmem] = transformUBO[frame];
        transform.rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, (t++) * 0.001f, 0.0f));
        tmem->upload_data(device, &transform, sizeof(Transform));

        auto& [_1, cmem] = cameraUBO[frame];
        cameraTransform.proj = Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f);
        cmem->upload_data(device, &cameraTransform, sizeof(CameraTransform));

        // Todo, we need to fix this
        auto handles = Handles {static_cast<u32>(frame + 3), static_cast<u32>(frame) };

        auto& cmd = commandBuffers[frame];

        cmd->begin_record()
            .begin_render_pass(swapChain, frame)
            .set_viewport(0, 0, window->get_width(), window->get_height())
            .bind_pipeline(pipeline)
            .bind_descriptor_set(pipelineLayout, descriptors, frame)
            .bind_vertex_buffer(vbuffer)
            .bind_index_buffer(ibuffer)
            .push_constant(pipelineLayout, sizeof(Handles), 0, &handles)
            .draw_indexed(indices.size())
            .end_render_pass()
            .end_record();

        if(!swapChain->submit_command_buffers(device, cmd, &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    device->wait_idle();

    device->destroy_all(commandBuffers);
    device->destroy_all(vbuffer, ibuffer, vmemory, imemory, commandBufferPool);

    for(auto& [buffer, memory] : transformUBO)
        device->destroy_all(buffer, memory);

    for(auto& [buffer, memory] : cameraUBO)
        device->destroy_all(buffer, memory);

    device->destroy_all(descriptorSetLayout);
    device->destroy_all(descriptors);
    device->destroy_all(descriptorPool, vertShaderModule,fragShaderModule,pipelineLayout,pipeline, swapChain);

    device->destroy();
    instance->destroy();

    // Todo move all glfw things to glfw context static class
    GLFWContext::terminate();

    return 0;
}
