#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;

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
const auto vertex_descriptions = VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
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
    auto swap_chain = device->create_swap_chain(window);

    auto vert_shader_module = device->create_shader_module("vert.glsl", ShaderTypes::vertex_shader);
    auto frag_shader_module = device->create_shader_module("frag.glsl", ShaderTypes::fragment_shader);
    auto pipeline_layout = device->create_pipeline_layout({}, {});
    auto pipeline = device->create_pipeline(swap_chain->render_pass, pipeline_layout, { vert_shader_module, frag_shader_module }, {
        .vertex_input_state = { .vertex_descriptions = vertex_descriptions }
    });

    auto vb = device->create_buffer_memory_from(vertices);
    auto eb = device->create_buffer_memory_from(indices);

    auto command_buffer_pool = device->create_command_buffer_pool();
    auto command_buffers = command_buffer_pool->create_command_buffers(device, 3);

    while (!window->closing()) {
        GLFWContext::poll_events();

        uint32_t frame;
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto& cmd = command_buffers[frame];

        cmd->begin_record();

        cmd->begin_render_pass(swap_chain);
            cmd->set_viewport(0, 0, window->get_width(), window->get_height());
            cmd->bind_pipeline(pipeline);
            cmd->bind_vertex_buffer(vb);
            cmd->bind_index_buffer(eb);
            cmd->draw_indexed(indices.size());
        cmd->end_render_pass();

        cmd->end_record();

        if(!swap_chain->submit_present_command_buffers(device, cmd, &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    instance->destroy();

    GLFWContext::terminate();

    return 0;
}
