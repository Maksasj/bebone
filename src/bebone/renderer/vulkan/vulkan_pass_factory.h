#ifndef _BEBONE_RENDERER_VULKAN_PASS_FACTORY_H_
#define _BEBONE_RENDERER_VULKAN_PASS_FACTORY_H_

#include "irenderer.h"
#include "vulkan_pass_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPassImplFactory : public IPassImplFactory {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

        public:
            VulkanPassImplFactory(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain);
        
            std::shared_ptr<IPassImpl> create_present_pass_impl() override;
            std::shared_ptr<IPassImpl> create_deferred_g_pass_impl(const Vec2i& viewport) override;
    };
}

#endif
