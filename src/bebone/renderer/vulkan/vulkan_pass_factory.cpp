#include "vulkan_pass_factory.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanPassFactory::VulkanPassFactory(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanPipelineManager>& pipeline_manager
    ) : device(device), swap_chain(swap_chain), pipeline_manager(pipeline_manager) {

    }

    std::shared_ptr<IPresentPass> VulkanPassFactory::create_present_pass(const std::string& pass_name) {
        return std::make_shared<VulkanPresentPass>(pass_name);
    }

    std::shared_ptr<IRenderQueuePass> VulkanPassFactory::create_geometry_pass(const std::string& pass_name) {
        return std::make_shared<VulkanGeometryPass>(pass_name);
    }
}
