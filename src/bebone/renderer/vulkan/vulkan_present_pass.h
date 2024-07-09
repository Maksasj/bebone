#ifndef _BEBONE_RENDERER_VULKAN_PRESENT_PASS_H_
#define _BEBONE_RENDERER_VULKAN_PRESENT_PASS_H_

#include "../irenderer.h"
#include "../ipass.h"
#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanPresentPass : public IPresentPass {
        private:
            std::shared_ptr<VulkanDevice> device;
            std::shared_ptr<VulkanSwapChain> swap_chain;

            std::optional<VulkanManagedPipelineTuple> pipeline;

        public:
            VulkanPresentPass(
                const std::string& pass_name,
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanSwapChain>& swap_chain,
                std::shared_ptr<VulkanPipelineManager>& pipeline_manager);

            void assemble(IPassAssembler* assember) override;

            void record(ICommandEncoder* encoder) override;
            void reset() override;
    };
}

#endif
