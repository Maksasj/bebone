#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <fstream>

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#include "bebone/bebone.h"

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

using namespace bebone::gfx;
using namespace omni::types;

const std::vector<Vertex> vertices = {
    {{-1.0f, -1.0f,  1.0}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 1.0f, -1.0f,  1.0}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f,  1.0f,  1.0}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f,  1.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-1.0f, -1.0f, -1.0}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
    {{ 1.0f, -1.0f, -1.0}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{-1.0f,  1.0f, -1.0}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
    {{ 1.0f,  1.0f, -1.0}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}
};

const std::vector<int> indices = {
    2, 6, 7, 2, 3, 7, //Top
    0, 4, 5, 0, 1, 5, //Bottom
    0, 2, 6, 0, 4, 6, //Left
    1, 3, 7, 1, 5, 7, //Right
    0, 2, 3, 0, 1, 3, //Front
    4, 6, 7, 4, 5, 7  //Back
};

int main() {
    RenderingEngine::preinit();

    std::vector<unsigned int> vertexSpirvCode, fragmentSpirvCode;

    ShaderCompiler::compile_shader(read_file("assets/vert.glsl").c_str(), EShLangVertex, vertexSpirvCode);
    ShaderCompiler::compile_shader(read_file("assets/frag.glsl").c_str(), EShLangFragment, fragmentSpirvCode);

    Window window("Client", 800, 600);
    VulkanRenderer renderer = VulkanRenderer(window);
    GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();

    struct Handles {
        unsigned int transform;
        unsigned int camera;
    };

    struct Transform {
        Mat4f transform;
        Mat4f scale;
        Mat4f rotation;
    };

    struct Camera {
        Mat4f view;
        Mat4f proj;
    };

    GPUResourceSet resourceSet = resourceManager
        .create_resource_set()
        .set_uniform_buffer_resource(0)
        .set_uniform_buffer_resource(1)
        .build();

    PipelineLayout pipelineLayout = renderer
        .create_pipeline_layout_builder()
        .set_constant_range(0, sizeof(Handles))
        .build(resourceManager);

    Pipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);
    
    UniformBuffer<Transform> tUbo0 = resourceManager.create_uniform_buffer<Transform>(resourceSet, 0);
    UniformBuffer<Transform> tUbo1 = resourceManager.create_uniform_buffer<Transform>(resourceSet, 0);

    UniformBuffer<Camera> cameraUbo = resourceManager.create_uniform_buffer<Camera>(resourceSet, 1);
    
    VertexBuffer vertexBuffer = renderer.create_vertex_buffer(vertices);
    IndexBuffer indexBuffer = renderer.create_index_buffer(indices);

    VulkanCommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();

    Transform t0 = {
        Mat4f::translation(Vec3f(1.0f, 0.0f, 2.5f)),
        Mat4f::scale(0.3f),
        Mat4f::rotation_y(0.4f)
    };

    Transform t1 = {
        Mat4f::translation(Vec3f(-1.0f, 0.0f, 2.5f)),
        Mat4f::scale(0.3f),
        Mat4f::rotation_y(0.4f)
    };

    Camera c = {
        Mat4f::translation(Vec3f(0.0f, 0.0f, 0.0f)),
        Mat4f::perspective(1.0472, window.get_aspect(), 0.1f, 10.0f)
    };

    f32 f = 0;
    while (!window.closing()) {
        f += 0.001f;
        glfwPollEvents();

        uint32_t frame = renderer.get_frame();

        VulkanCommandBuffer& cmd = commandBufferPool.get_command_buffer(frame);

        t0.rotation = trait_bryan_angle_yxz(Vec3f(f, f, 0.0f));
        t1.rotation = trait_bryan_angle_yxz(Vec3f(0.0f, f, 0.0f));
        t1.transform = Mat4f::translation(Vec3f(-1.0f, 0.0f, 2.5f + sin(f)));

        tUbo0.get_impl(frame)->set_data(t0);
        tUbo1.get_impl(frame)->set_data(t1);
        cameraUbo.get_impl(frame)->set_data(c);

        cmd.begin_record();
            cmd.begin_render_pass(renderer, frame);
            cmd.set_viewport(0, 0, window.get_width(), window.get_height());

            cmd.bind_pipeline(pipeline);
            resourceSet.bind(cmd, pipelineLayout);

            cmd.bind_vertex_buffer(vertexBuffer);
            cmd.bind_index_buffer(indexBuffer);

            Handles h1 = {
                static_cast<u32>(tUbo1.get_handle(frame).index),
                static_cast<u32>(cameraUbo.get_handle(frame).index)
            };

            cmd.push_constant(pipelineLayout, sizeof(Handles), &h1);
            cmd.draw_indexed(indices.size());
            
            Handles h0 = {
                static_cast<u32>(tUbo0.get_handle(frame).index),
                static_cast<u32>(cameraUbo.get_handle(frame).index)
            };

            cmd.push_constant(pipelineLayout, sizeof(Handles), &h0);
            cmd.draw_indexed(indices.size());

            cmd.end_render_pass();
        cmd.end_record();

        cmd.submit();

        renderer.present(frame);
    }

    vkDeviceWaitIdle(renderer.device->device());

    glfwTerminate();

    return 0; 
}