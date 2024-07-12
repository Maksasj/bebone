#include "vulkan_pass_factory.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    VulkanPassFactory::VulkanPassFactory(
        const std::shared_ptr<VulkanDevice>& device,
        const std::shared_ptr<VulkanSwapChain>& swap_chain,
        const std::shared_ptr<VulkanPipelineManager>& pipeline_manager
    ) : device(device), swap_chain(swap_chain), pipeline_manager(pipeline_manager) {

    }

    std::shared_ptr<IPresentPass> VulkanPassFactory::create_present_pass(const std::string& pass_name, const Vec2i& viewport) {
        return std::make_shared<VulkanPresentPass>(pass_name, viewport);
    }

    std::shared_ptr<IDeferredGPass> VulkanPassFactory::create_deferred_g_pass(const std::string& pass_name, const Vec2i& viewport) {
        return std::make_shared<VulkanDeferredGPass>(pass_name, viewport);
    }
}
