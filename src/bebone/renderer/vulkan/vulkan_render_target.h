#ifndef _BEBONE_RENDERER_VULKAN_RENDER_TARGET_H_
#define _BEBONE_RENDERER_VULKAN_RENDER_TARGET_H_

#include "../irender_target.h"
#include "../iattachment.h"
#include "vulkan_texture_impl.h"
#include "vulkan_texture_manager.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderTarget : public IRenderTarget {
        private:
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

        public:
            VulkanRenderTarget(const std::shared_ptr<VulkanSwapChain>& swap_chain);
            VulkanRenderTarget(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<gfx::VulkanRenderPass>& render_pass,
                const std::shared_ptr<VulkanTextureManager>& texture_manager,
                const std::vector<std::shared_ptr<IAttachment>>& attachments,
                const Vec2i& viewport);
    };
}

#endif
