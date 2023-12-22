#include <iostream>
#include <fstream>

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

struct Vertex {
    Vec3f pos;
    Vec3f color;
};

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

const std::vector<int> indices = {
    0, 1, 2, 2, 3, 0,
    1, 5, 6, 6, 2, 1,
    7, 6, 5, 5, 4, 7,
    4, 0, 3, 3, 7, 4,
    4, 5, 1, 1, 0, 4,
    3, 2, 6, 6, 7, 3
};

struct Handles {
    u32 cameraHandle;
    u32 transformHandle;
};

struct CameraTransform {
    Mat4f view;
    Mat4f proj;
};

struct Transform {
    Mat4f transform;
    Mat4f scale;
    Mat4f rotation;
};

Mat4f getViewMatrix(Vec3f position, Vec3f direction, Vec3f up);

int main() {
    RenderingEngine::preinit();

    auto window = WindowFactory::create_window("2. Vulkan 3d cube example", 800, 600, GfxAPI::VULKAN);
    auto renderer = VulkanRenderer(window);

    auto descriptorPool = std::make_shared<VulkanDescriptorPool>(*renderer.device);

    auto descriptorSetLayout = renderer.device->create_descriptor_set_layouts({
          {
              .binding = 0,
              .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
              .descriptorCount = 65536,
              .stageFlags = VK_SHADER_STAGE_ALL,
              .pImmutableSamplers = nullptr
          },
          {
              .binding = 1,
              .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
              .descriptorCount = 65536, // Todo this is max thing
              .stageFlags = VK_SHADER_STAGE_ALL, // Todo this should be confiruble
              .pImmutableSamplers = nullptr // Optional
          },
      });

    auto descriptors = std::vector<std::shared_ptr<VulkanDescriptorSet>>({
        descriptorPool->create_descriptor_bindless(renderer.device, descriptorSetLayout[0]),
        descriptorPool->create_descriptor_bindless(renderer.device, descriptorSetLayout[0]),
        descriptorPool->create_descriptor_bindless(renderer.device, descriptorSetLayout[0])
    });

    auto pipelineLayout = renderer.device->create_pipeline_layout(descriptorSetLayout, {{
        .stageFlags = (VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT),
        .offset = 0,
        .size = sizeof(Handles)
    }});

    auto vertShaderModule = renderer.device->create_shader_module("examples/assets/gfx/vulkan/2_vulkan_3d_cube/vert.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragShaderModule = renderer.device->create_shader_module("examples/assets/gfx/vulkan/2_vulkan_3d_cube/frag.glsl", ShaderTypes::FRAGMENT_SHADER);

    auto pipeline = renderer.device->create_pipeline(renderer.swapChain, pipelineLayout, vertShaderModule, fragShaderModule);

    auto vertexBuffer = renderer.device->create_buffer(sizeof(Vertex) * vertices.size());
    auto indexBuffer = renderer.device->create_buffer(sizeof(u32) * indices.size());

    vertexBuffer->upload_data(vertices.data(), sizeof(Vertex) * vertices.size());
    indexBuffer->upload_data(indices.data(), sizeof(u32) * indices.size());

    auto transformUBO = renderer.device->create_buffers(sizeof(Transform), 3);
    auto cameraUBO = renderer.device->create_buffers(sizeof(CameraTransform), 3);

    descriptorPool->update_descriptor_sets(transformUBO[0], sizeof(Transform), descriptors[0], 0, 0);
    descriptorPool->update_descriptor_sets(transformUBO[1], sizeof(Transform), descriptors[1], 0, 1);
    descriptorPool->update_descriptor_sets(transformUBO[2], sizeof(Transform), descriptors[2], 0, 2);

    descriptorPool->update_descriptor_sets(cameraUBO[0], sizeof(CameraTransform), descriptors[0], 1, 0 + 3);
    descriptorPool->update_descriptor_sets(cameraUBO[1], sizeof(CameraTransform), descriptors[1], 1, 1 + 3);
    descriptorPool->update_descriptor_sets(cameraUBO[2], sizeof(CameraTransform), descriptors[2], 1, 2 + 3);

    auto cameraTransform = CameraTransform{
        getViewMatrix(Vec3f(0.0f, 0.0f, 10.0f), Vec3f(0.0f, 0.0f, -1.0f), Vec3f(0.0f, -1.0f, 0.0f)),
        Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f)
    };

    auto transform = Transform{
        Mat4f::translation(Vec3f::splat(0.0f)),
        Mat4f::scale(1.0f),
        Mat4f::identity()
    };

    f32 t = 0.0f;
    while (!window->closing()) {
        glfwPollEvents();

        auto frame = renderer.get_frame();

        if(!frame.valid())
            continue;

        transform.rotation = trait_bryan_angle_yxz(Vec3f(t * 0.001f, t * 0.001f, 0.0f));
        cameraTransform.proj = Mat4f::perspective(1.0472, window->get_aspect(), 0.1f, 100.0f);
        ++t;

        auto handles = Handles {
            static_cast<u32>(frame.frameIndex + 3),
            static_cast<u32>(frame.frameIndex )
        };
        
        auto& cmd = frame.get_command_buffer();

        cmd.begin_record();
            cmd.begin_render_pass(renderer.swapChain, frame.frameIndex);
            cmd.set_viewport(0, 0, window->get_width(), window->get_height());

            cmd.bind_pipeline(*pipeline);

            cmd.bind_descriptor_set(pipelineLayout, descriptors[frame.frameIndex]->descriptorSet);

            cmd.bind_vertex_buffer(vertexBuffer);
            cmd.bind_index_buffer(indexBuffer);

            transformUBO[frame.frameIndex]->upload_data(&transform, sizeof(Transform));
            cameraUBO[frame.frameIndex]->upload_data(&cameraTransform, sizeof(CameraTransform));

            cmd.push_constant(pipelineLayout, sizeof(Handles), 0, &handles);

            cmd.draw_indexed(indices.size());

            cmd.end_render_pass();
        cmd.end_record();

        renderer.present(frame);
    }

    renderer.device->wait_idle();

    glfwTerminate();

    return 0;
}

Mat4f getViewMatrix(Vec3f position, Vec3f direction, Vec3f up) {
    const Vec3f w = direction.normalize();
    const Vec3f u = w.cross(up).normalize();
    const Vec3f v = w.cross(u);

    Mat4f viewMatrix = Mat4f::identity();
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
