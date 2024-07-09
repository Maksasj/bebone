#include "vulkan_render_graph.h"

namespace bebone::renderer {
    VulkanRenderGraph::VulkanRenderGraph(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain
    ) : IRenderGraph(), device(device), swap_chain(swap_chain) {
        pipeline_manager = device->create_pipeline_manager();
        command_buffers = device->create_command_buffers(3);
    }

    void VulkanRenderGraph::record() {
        uint32_t frame;

        if(!swap_chain->acquire_next_image(device, &frame).is_ok())
            return;

        auto& cmd = command_buffers[frame];
        VulkanCommandEncoder encoder(cmd, frame);

        cmd->begin_record();

        for(auto& pass : get_render_passes()) {
            pass->record(&encoder);
        }

        cmd->end_record();

        if(!swap_chain->submit_present_command_buffers(device, command_buffers[frame], &frame).is_ok()) // Todo check if window is resized
            return;
    }

    void VulkanRenderGraph::submit() {

    }

    void VulkanRenderGraph::reset() {

    }

    std::shared_ptr<IPassFactory> VulkanRenderGraph::create_pass_factory() const {
        return std::make_shared<VulkanPassFactory>(device, swap_chain, pipeline_manager);
    }
}
