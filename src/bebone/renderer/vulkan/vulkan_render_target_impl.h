#ifndef _BEBONE_RENDERER_VULKAN_RENDER_TARGET_IMPL_H_
#define _BEBONE_RENDERER_VULKAN_RENDER_TARGET_IMPL_H_

#include "../irender_target_impl.h"
#include "../iattachment.h"
#include "vulkan_texture_impl.h"
#include "vulkan_texture_manager.h"
#include "vulkan_attachment_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRenderTargetImpl : public IRenderTargetImpl {
        private:
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

        public:
            VulkanRenderTargetImpl(const std::shared_ptr<VulkanSwapChain>& swap_chain);

            VulkanRenderTargetImpl(
                const std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<gfx::VulkanRenderPass>& render_pass,
                const std::shared_ptr<VulkanTextureManager>& texture_manager,
                const std::vector<std::shared_ptr<IAttachment>>& attachments,
                const Vec2i& viewport);

            const std::vector<std::shared_ptr<VulkanFramebuffer>>& get_framebuffers();
    };
}

#endif
