#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;

// Todo make this nicer
const auto vertex_descriptions = VulkanPipelineVertexInputStateTuple {
    .binding_descriptions = {
        { 0, sizeof(Vec3f), VK_VERTEX_INPUT_RATE_VERTEX }
    },
    .attribute_descriptions = {
        { 0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0 }
    }
};

int main() {
    auto window = WindowFactory::create_window("1. Vulkan hello triangle example", 800, 600, Vulkan);

    VulkanInstance instance;
    VulkanDevice device(instance, window);
    VulkanSwapChain swap_chain(device, window);

    VulkanPipelineLayout pipeline_layout(device, {}, {});
    VulkanPipeline pipeline(device, swap_chain.render_pass, pipeline_layout, "vert.glsl", "frag.glsl", { .vertex_input_state = { .vertex_descriptions = vertex_descriptions } });

    const std::vector<Vec3f> vertices = { {-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.0f,  0.5f, 0.0f} };
    const std::vector<u32> indices = { 0, 1, 2, };

    VulkanBufferMemory vb(device, vertices);
    VulkanBufferMemory eb(device, indices);

    VulkanCommandBufferPool command_buffer_pool(device);
    auto command_buffers = command_buffer_pool.create_command_buffers(3);

    while (!window->closing()) {
        window->pull_events();

        uint32_t frame;
        if(!swap_chain.acquire_next_image(&frame).is_ok())
            continue;

        unique_ptr<VulkanCommandBuffer>& cmd = command_buffers[frame];

        cmd->begin_record();

        cmd->begin_render_pass(swap_chain);
            cmd->set_viewport(window);
            cmd->bind_pipeline(pipeline);
            cmd->bind_vertex_buffer(vb)
                .bind_index_buffer(eb)
                .draw_indexed(indices.size());
        cmd->end_render_pass();

        cmd->end_record();

        if(!swap_chain.submit_present_command_buffers(*cmd, &frame).is_ok()) // Todo check if window is resized
            continue;
    }

    return 0;
}
