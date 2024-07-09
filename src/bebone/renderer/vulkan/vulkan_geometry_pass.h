#ifndef _BEBONE_RENDERER_VULKAN_GEOMETRY_PASS_H_
#define _BEBONE_RENDERER_VULKAN_GEOMETRY_PASS_H_

#include "../irenderer.h"
#include "../ipass.h"
#include "vulkan_command_encoder.h"

namespace bebone::renderer {
    class VulkanGeometryPass : public IGeometryPass {
        private:
            std::shared_ptr<VulkanDevice> device;

            std::optional<VulkanManagedPipelineTuple> pipeline;
            std::shared_ptr<VulkanRenderTarget> render_target;
            std::shared_ptr<VulkanRenderPass> render_pass;

        public:
            VulkanGeometryPass(
                const std::string& pass_name,
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanPipelineManager>& pipeline_manager);

            void assemble(IPassAssembler* assember) override;

            void record(ICommandEncoder* encoder) override;
            void reset() override;
    };
}

#endif
