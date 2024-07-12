#ifndef _BEBONE_RENDERER_VULKAN_DEFERRED_G_PASS_H_
#define _BEBONE_RENDERER_VULKAN_DEFERRED_G_PASS_H_

#include "../irenderer.h"
#include "../ipass.h"
#include "vulkan_command_encoder.h"
#include "vulkan_pass_assembler.h"
#include "vulkan_texture_resource.h"
#include "vulkan_depth_resource.h"
#include "../ideferred_g_pass.h"
#include "vulkan_program.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class VulkanDeferredGPass : public IDeferredGPass {
        private:
            std::shared_ptr<VulkanRenderPass> render_pass;
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

        public:
            VulkanDeferredGPass(const std::string& pass_name, const Vec2i& viewport);

            void assemble(IPassAssembler* assember) override;

            void record(ICommandEncoder* encoder) override;
            void reset() override;
    };
}

#endif
