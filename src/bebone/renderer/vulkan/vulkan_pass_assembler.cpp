#include "vulkan_pass_assembler.h"

namespace bebone::renderer {
    VulkanPassAssembler::VulkanPassAssembler(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanPipelineManager>& pipeline_manager
    ) : device(device), swap_chain(swap_chain), pipeline_manager(pipeline_manager) {

    }

    std::shared_ptr<VulkanDevice> VulkanPassAssembler::get_device() const {
        return device;
    }

    std::shared_ptr<VulkanSwapChain> VulkanPassAssembler::get_swap_chain() const {
        return swap_chain;
    }

    std::shared_ptr<VulkanPipelineManager> VulkanPassAssembler::get_pipeline_manager() const {
        return pipeline_manager;
    }
}
