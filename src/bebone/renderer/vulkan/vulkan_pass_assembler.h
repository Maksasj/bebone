#ifndef _BEBONE_RENDERER_VULKAN_PASS_ASSEMBLER_H_
#define _BEBONE_RENDERER_VULKAN_PASS_ASSEMBLER_H_

#include "../renderer_backend.h"
#include "ipass_assembler.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPassAssembler : public IPassAssembler {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;
            std::shared_ptr<VulkanPipelineManager> pipeline_manager;

        public:
            VulkanPassAssembler(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<VulkanPipelineManager>& pipeline_manager);

            std::shared_ptr<VulkanDevice> get_device() const;
            std::shared_ptr<VulkanSwapChain> get_swap_chain() const;
            std::shared_ptr<VulkanPipelineManager> get_pipeline_manager() const;
    };
}

#endif