#include <iostream>
#include <fstream>

#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, 0},
    {{0.5f, 0.5f, 0.0f},  {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, 0},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}, 0},
};

const std::vector<int> indices = {
    0, 1, 2
};

std::string read_file(const std::string& path);

int main() {
    RenderingEngine::preinit();

    Window window("1. Vulkan hello window example", 800, 600, GfxAPI::VULKAN);

    auto renderer = VulkanRenderer(window);
    
    auto resourceManager = renderer.create_gpu_resource_manager();

    auto pipelineLayout = renderer
        .create_pipeline_layout_builder()
        .build(resourceManager);

    ShaderCode vertexShaderCode(ShaderTypes::VERTEX_SHADER);
    ShaderCode fragmentShaderCode(ShaderTypes::FRAGMENT_SHADER);

    {   // Compiling glsl vertex shader code;
        ShaderCompiler shaderCompiler;
        
        shaderCompiler.add_shader_source(ShaderSource(
            read_file("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/vert.glsl"),
            ShaderTypes::VERTEX_SHADER
        ));
        vertexShaderCode = shaderCompiler.compile(ShaderTypes::VERTEX_SHADER);
    }

    {   // Compiling glsl fragment shader code;
        ShaderCompiler shaderCompiler;
        
        shaderCompiler.add_shader_source(ShaderSource(
            read_file("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/frag.glsl"),
            ShaderTypes::FRAGMENT_SHADER
        ));
        fragmentShaderCode = shaderCompiler.compile(ShaderTypes::FRAGMENT_SHADER);
    }

    auto pipeline = renderer.create_pipeline(pipelineLayout, vertexShaderCode, fragmentShaderCode);

    auto vertexBuffer = VertexBuffer(renderer.create_vertex_buffer_impl(vertices));
    auto indexBuffer = IndexBuffer(renderer.create_index_buffer_impl(indices));

    while (!window.closing()) {
        glfwPollEvents();

        auto frame = renderer.get_frame();

        if(!frame.valid())
            continue;

        auto& cmd = frame.get_command_buffer();

        cmd.begin_record();
            cmd.begin_render_pass(renderer, frame.frameIndex);
            cmd.set_viewport(0, 0, window.get_width(), window.get_height());

            cmd.bind_pipeline(pipeline);

            cmd.bind_vertex_buffer(vertexBuffer);
            cmd.bind_index_buffer(indexBuffer);

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

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
