#include <iostream>
#include <fstream>

#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

const std::vector<Vertex> vertices = {
    {{0.0f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
    
};

const std::vector<int> indices = {
    0, 1, 2
};

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

int main() {
    RenderingEngine::preinit();

    Window window("Vulkan window", 800, 600);

    VulkanRenderer renderer = VulkanRenderer(window);
    
    GPUResourceManager resourceManager = renderer.create_gpu_resource_manager();
    GPUResourceSet resourceSet = resourceManager
        .create_resource_set()
        .set_uniform_buffer_resource(0)
        .build();

    PipelineLayout pipelineLayout = renderer
        .create_pipeline_layout_builder()
        .build(resourceManager);

    std::vector<unsigned int> vertexSpirvCode;
    std::vector<unsigned int> fragmentSpirvCode;

    ShaderCompiler::compile_shader(read_file("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/vert.glsl").c_str(), EShLangVertex, vertexSpirvCode);
    ShaderCompiler::compile_shader(read_file("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/frag.glsl").c_str(), EShLangFragment, fragmentSpirvCode);

    Pipeline pipeline = renderer.create_pipeline(pipelineLayout, vertexSpirvCode, fragmentSpirvCode);

    VulkanCommandBufferPool& commandBufferPool = renderer.get_command_buffer_pool();

    VertexBuffer vertexBuffer = VertexBuffer(renderer.create_vertex_buffer_impl(vertices));
    IndexBuffer indexBuffer = IndexBuffer(renderer.create_index_buffer_impl(indices));

    while (!window.closing()) {
        glfwPollEvents();

        uint32_t frame = renderer.get_frame();
        if(frame == 9999)
            continue;

        VulkanCommandBuffer& cmd = commandBufferPool.get_command_buffer(frame);

        cmd.begin_record();
            cmd.begin_render_pass(renderer, frame);
            cmd.set_viewport(0, 0, window.get_width(), window.get_height());

            cmd.bind_pipeline(pipeline);
            resourceSet.bind(cmd, pipelineLayout);

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