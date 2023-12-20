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
    auto renderer = VulkanRenderer(window);

    /*
    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swapchain = device->create_swap_chain();

    auto descriptorPool = device->create_descriptor_pool();
    auto descriptorSetLayout = descriptorPool->create_descriptor_set_layout();
    auto descriptorSet = descriptorPool->create_descriptor_set(descriptorSetLayout);

    auto vertexBuffer = device->create_buffer(sizeof(Vertex) * vertices.size());
    auto indexBuffer = device->create_buffer(sizeof(u32) * indices.size());

    auto pipelineLayout = device-create_pipeline_layout();

    auto pipeline = device->create_pipeline(pipelineLayout);

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool-create_command_buffers(3); // An array of command buffers

    device->wait_idle();
    */

    auto descriptorPool = VulkanDescriptorPool(*renderer.device);
    auto pipelineLayout = VulkanPipelineLayoutImpl(*renderer.device, descriptorPool, {});

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
    pipelineConfig.renderPass = renderer.swapChain->renderTarget->renderPass.renderPass;
    pipelineConfig.pipelineLayout = pipelineLayout.get_layout();
    auto pipeline = std::make_shared<VulkanPipeline>(*renderer.device, vertexShaderCode, fragmentShaderCode, pipelineConfig);

    auto vertexBuffer = VertexBuffer(new VulkanVertexBufferImpl(vertices, *renderer.device));
    auto indexBuffer = IndexBuffer(new VulkanIndexBufferImpl(indices, *renderer.device));

    auto commandBufferPool = renderer.commandBuffers;

    while (!window->closing()) {
        glfwPollEvents();

        uint32_t frameIndex;

        {
            auto result = renderer.swapChain->acquireNextImage(&frameIndex);

            if(result == VK_ERROR_OUT_OF_DATE_KHR)
                continue;

            if(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
                throw std::runtime_error("failed to acquire swap chain image!");
        }

        auto& cmd = renderer.commandBuffers->get_command_buffer(frameIndex);

        cmd.begin_record();
            cmd.begin_render_pass(renderer.swapChain, frameIndex);
            cmd.set_viewport(0, 0, window->get_width(), window->get_height());

            cmd.bind_pipeline(*pipeline);

            cmd.bind_vertex_buffer(vertexBuffer);
            cmd.bind_index_buffer(indexBuffer);

            cmd.draw_indexed(indices.size());

            cmd.end_render_pass();
        cmd.end_record();

        auto result = renderer.swapChain->submitCommandBuffers(&cmd.commandBuffer, &frameIndex);

        if(result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || window->is_resized())
            continue;

        if(result != VK_SUCCESS)
            throw std::runtime_error("failed to acquire submit command buffers !\n");
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
