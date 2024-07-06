#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::assets;
using namespace bebone::gfx;

struct Vertex {
    Vec3f pos;
    Vec3f color;
    Vec2f texCord;
};

const std::vector<Vertex> vertices {
    {{0.5f,  0.5f, 0.0f},    {1.0f, 0.0f, 0.0f},   {1.0f, 1.0f}},
    {{0.5f, -0.5f, 0.0f},    {0.0f, 1.0f, 0.0f},   {1.0f, 0.0f}},
    {{-0.5f, -0.5f, 0.0f},   {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},
    {{-0.5f,  0.5f, 0.0f},   {1.0f, 1.0f, 0.0f},   {0.0f, 1.0f}}
};

const std::vector<u32> indices {
    0, 1, 3, 1, 2, 3
};

// Todo make this nicer
const auto vertex_descriptions = VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(Vertex), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, pos) },
        { 1, 0, VK_FORMAT_R32G32B32_SFLOAT, offsetof(Vertex, color) },
        { 2, 0, VK_FORMAT_R32G32_SFLOAT, offsetof(Vertex, texCord) }
    }
};

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("2. Vulkan texture example", 800, 600, Vulkan);

    auto instance = VulkanInstance::create_instance();
    auto device = instance->create_device(window);
    auto swap_chain = device->create_swap_chain(window);

    auto pipeline_manager = device->create_pipeline_manager();

    auto pipeline = pipeline_manager->create_pipeline(
        device, swap_chain, "vert.glsl", "frag.glsl",
        { }, { {BindlessSampler, 0} },
        { .vertex_input_state = { .vertex_descriptions = vertex_descriptions } }
    );

    auto vb = device->create_buffer_memory_from(vertices);
    auto eb = device->create_buffer_memory_from(indices);

    auto command_buffer_pool = device->create_command_buffer_pool();
    auto command_buffers = command_buffer_pool->create_command_buffers(device, 3);

    auto texture = device->create_texture(command_buffer_pool, "image.png");
    std::ignore = pipeline.bind_texture(device, texture, 0);

    while (!window->closing()) {
        GLFWContext::poll_events();

        uint32_t frame;
        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            continue;

        auto& cmd = command_buffers[frame];

        cmd->begin_record()
            .begin_render_pass(swap_chain, frame)
            .set_viewport(0, 0, window->get_width(), window->get_height())
            .bind_managed_pipeline(pipeline, frame)
            .bind_vertex_buffer(vb)
            .bind_index_buffer(eb)
            .draw_indexed(indices.size())
            .end_render_pass()
            .end_record();

        if(!swap_chain->submit_command_buffers(device, cmd, &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    instance->destroy();

    GLFWContext::terminate();

    return 0;
}
