#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::gfx::vulkan;

struct Vertex {
    Vec3f pos;
    Vec3f color;
};

const std::vector<Vertex> vertices = {
    {{0.5f, 0.5f, 0.0f},  {1.0f, 0.0f, 0.0f}},
    {{0.0f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}},
    {{-0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}},
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

const std::vector<int> indices = { 0, 1, 2 };

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("1. Vulkan hello window example", 800, 600, GfxAPI::Vulkan);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swapChain = device->create_swap_chain(window);

    auto vertShaderModule = device->create_shader_module("vert.glsl", ShaderTypes::VERTEX_SHADER);
    auto fragShaderModule = device->create_shader_module("frag.glsl", ShaderTypes::FRAGMENT_SHADER);
    auto pipelineLayout = device->create_pipeline_layout({}, {});
    auto pipeline = device->create_pipeline(swapChain, pipelineLayout, { vertShaderModule, fragShaderModule }, {
        .pVertexInputState = { .vertexDescriptions = vertexDescriptions }
    });

    auto [ vbuffer, vmemory ] = device->create_buffer_memory_from(vertices);
    auto [ ibuffer, imemory ] = device->create_buffer_memory_from(indices);

    auto commandBufferPool = device->create_command_buffer_pool();
    auto commandBuffers = commandBufferPool->create_command_buffers(device, 3);

    while (!window->closing()) {
        GLFWContext::poll_events();

        uint32_t frame;
        if(!swapChain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto& cmd = commandBuffers[frame];

        cmd->begin_record()
            .begin_render_pass(swapChain, frame)
            .set_viewport(0, 0, window->get_width(), window->get_height())
            .bind_pipeline(pipeline)
            .bind_vertex_buffer(vbuffer)
            .bind_index_buffer(ibuffer)
            .draw_indexed(indices.size())
            .end_render_pass()
            .end_record();

        if(!swapChain->submit_command_buffers(device, cmd, &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    device->wait_idle();

    device->destroy_all(commandBuffers); // Todo \/ lets make all tuples also destroyable
    device->destroy_all(vbuffer, ibuffer, vmemory, imemory, commandBufferPool);
    device->destroy_all(vertShaderModule,fragShaderModule,pipelineLayout,pipeline, swapChain);

    device->destroy();
    instance->destroy();

    GLFWContext::terminate();

    return 0;
}
