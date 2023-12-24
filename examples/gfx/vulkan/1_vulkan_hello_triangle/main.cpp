#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

struct Vertex {
    Vec3f pos;
    Vec3f color;
};

const std::vector<Vertex> vertices = {
    {{0.5f, 0.5f, 0.0f},  {1.0f, 0.0f, 0.0f}},
    {{0.0f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
};

const std::vector<int> indices = { 0, 1, 2 };

int main() {
    RenderingEngine::preinit();

    auto window = WindowFactory::create_window("1. Vulkan hello window example", 800, 600, GfxAPI::VULKAN);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swapChain = device->create_swap_chain(window);

    auto vertShaderModule = device->create_shader_module("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/vert.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragShaderModule = device->create_shader_module("examples/assets/gfx/vulkan/1_vulkan_hello_triangle/frag.glsl", ShaderTypes::FRAGMENT_SHADER);
    auto pipelineLayout = device->create_pipeline_layout({}, {});
    auto pipeline = device->create_pipeline(swapChain, pipelineLayout, vertShaderModule, fragShaderModule);

    auto vertexBuffer = device->create_buffer(sizeof(Vertex) * vertices.size());
    auto indexBuffer = device->create_buffer(sizeof(u32) * indices.size());
    vertexBuffer->upload_data(device, vertices.data(), sizeof(Vertex) * vertices.size());
    indexBuffer->upload_data(device, indices.data(), sizeof(u32) * indices.size());

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool->create_command_buffers(device, 3);

    while (!window->closing()) {
        glfwPollEvents();

        uint32_t frame;
        auto result = swapChain->acquire_next_image(device, &frame);

        if(result.is_ok())
            continue;

        auto& cmd = commandBuffers[frame];

        cmd->begin_record()
            .begin_render_pass(swapChain, frame)
            .set_viewport(0, 0, window->get_width(), window->get_height())
            .bind_pipeline(*pipeline)
            .bind_vertex_buffer(vertexBuffer)
            .bind_index_buffer(indexBuffer)
            .draw_indexed(indices.size())
            .end_render_pass()
            .end_record();

        result = swapChain->submit_command_buffers(device, cmd, &frame);

        if(result.is_ok() || window->is_resized())
            continue;
    }

    device->wait_idle();

    device->destroy_all(commandBuffers);
    device->destroy_all(vertexBuffer,indexBuffer,commandBufferPool);
    device->destroy_all(vertShaderModule,fragShaderModule,pipelineLayout,pipeline, swapChain);

    device->destroy();
    instance->destroy();

    glfwTerminate();

    return 0;
}
