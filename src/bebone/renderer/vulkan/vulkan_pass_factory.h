#ifndef _BEBONE_RENDERER_VULKAN_PASS_FACTORY_H_
#define _BEBONE_RENDERER_VULKAN_PASS_FACTORY_H_

#include "../irenderer.h"
#include "vulkan_pass.h"

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

            std::shared_ptr<IPresentPass> create_present_pass(const std::string& pass_name) override;
            std::shared_ptr<IGeometryPass> create_geometry_pass(const std::string& pass_name) override;
    };
}

#endif
