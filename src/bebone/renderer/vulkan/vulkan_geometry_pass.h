#ifndef _BEBONE_RENDERER_VULKAN_GEOMETRY_PASS_H_
#define _BEBONE_RENDERER_VULKAN_GEOMETRY_PASS_H_

#include "../irenderer.h"
#include "../ipass.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_assembler.h"
#include "vulkan_texture_resource.h"
#include "vulkan_depth_resource.h"

namespace bebone::renderer {
    class VulkanGeometryPass : public IRenderQueuePass {
        private:
            std::optional<VulkanManagedPipelineTuple> pipeline;
            std::shared_ptr<VulkanRenderPass> render_pass;
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

        public:
            VulkanGeometryPass(const std::string& pass_name);

            void assemble(IPassAssembler* assember) override;

            void record(ICommandEncoder* encoder) override;
            void reset() override;
    };
}

#endif
