#ifndef _BEBONE_RENDERER_VULKAN_PASS_FACTORY_H_
#define _BEBONE_RENDERER_VULKAN_PASS_FACTORY_H_

#include "../irenderer.h"

#include "vulkan_present_pass.h"
#include "vulkan_deferred_g_pass.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPassFactory : public IPassFactory {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;
            std::shared_ptr<VulkanPipelineManager> pipeline_manager;

        public:
            VulkanPassFactory(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<VulkanPipelineManager>& pipeline_manager);
        
            std::shared_ptr<IPresentPass> create_present_pass(const std::string& pass_name, const Vec2i& viewport) override;
            std::shared_ptr<IDeferredGPass> create_deferred_g_pass(const std::string& pass_name, const Vec2i& viewport) override;
    };
}

#endif
