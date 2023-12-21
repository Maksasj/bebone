#include <iostream>
#include <fstream>

#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

struct Vertex {
    Vec3f pos;
    Vec3f color;
};

const std::vector<Vertex> vertices = {
    {{0.5f, 0.5f, 0.0f},  {1.0f, 1.0f, 1.0f}},
    {{0.0f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}},
};

const std::vector<int> indices = {
    0, 1, 2
};

std::string read_file(const std::string& path);

int main() {
    RenderingEngine::preinit();

    auto window = WindowFactory::create_window("1. Vulkan hello window example", 800, 600, GfxAPI::VULKAN);
    auto instance = VulkanInstance::create_instance();

    auto device = instance->create_device(window);
    auto swapChain = device->create_swap_chain(window);

    auto descriptorPool = device->create_descriptor_pool();

    auto pipelineLayout = device->create_pipeline_layout(descriptorPool, {});

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool->create_command_buffers(3);

    ShaderCode vertexShaderCode(ShaderTypes::VERTEX_SHADER);
    ShaderCode fragmentShaderCode(ShaderTypes::FRAGMENT_SHADER);

    {   // Compiling glsl vertex shader code;
        SpirVShaderCompiler shaderCompiler;

        shaderCompiler.add_shader_source(ShaderSource(
            read_file("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/vert.glsl"),
            ShaderTypes::VERTEX_SHADER
        ));
        vertexShaderCode = shaderCompiler.compile(ShaderTypes::VERTEX_SHADER);
    }

    {   // Compiling glsl fragment shader code;
        SpirVShaderCompiler shaderCompiler;

        shaderCompiler.add_shader_source(ShaderSource(
            read_file("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/frag.glsl"),
            ShaderTypes::FRAGMENT_SHADER
        ));
        fragmentShaderCode = shaderCompiler.compile(ShaderTypes::FRAGMENT_SHADER);
    }

    PipelineConfigInfo pipelineConfig;
    PipelineConfigInfo::defaultPipelineConfigInfo(pipelineConfig);
    pipelineConfig.renderPass = swapChain->renderTarget->renderPass.renderPass;
    pipelineConfig.pipelineLayout = pipelineLayout->get_layout();
    auto pipeline = std::make_shared<VulkanPipeline>(*device, vertexShaderCode, fragmentShaderCode, pipelineConfig);

    auto vertexBuffer = device->create_buffer(sizeof(Vertex) * vertices.size());
    auto indexBuffer = device->create_buffer(sizeof(u32) * indices.size());

    vertexBuffer->upload_data(vertices.data(), sizeof(Vertex) * vertices.size());
    indexBuffer->upload_data(indices.data(), sizeof(u32) * indices.size());

    while (!window->closing()) {
        glfwPollEvents();

        uint32_t frameIndex;
        auto result = swapChain->acquireNextImage(&frameIndex);

        if(result == VK_ERROR_OUT_OF_DATE_KHR)
            continue;

        auto& cmd = commandBuffers[frameIndex];

        // Todo, maybe make this maybe channable ?
        cmd->begin_record();
            cmd->begin_render_pass(swapChain, frameIndex);
            cmd->set_viewport(0, 0, window->get_width(), window->get_height());

            cmd->bind_pipeline(*pipeline);

            cmd->bind_vertex_buffer(vertexBuffer);
            cmd->bind_index_buffer(indexBuffer);

            cmd->draw_indexed(indices.size());

            cmd->end_render_pass();
        cmd->end_record();

        result = swapChain->submitCommandBuffers(&cmd->commandBuffer, &frameIndex);

        if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window->is_resized())
            continue;
    }

    device->wait_idle();

    glfwTerminate();

    return 0;
}

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}
