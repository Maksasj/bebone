#ifndef _BEBONE_RENDERER_VULKAN_RENDER_TARGET_H_
#define _BEBONE_RENDERER_VULKAN_RENDER_TARGET_H_

#include "../irender_target.h"
#include "../iattachment.h"
#include "vulkan_texture_impl.h"

namespace bebone::renderer {
    using namespace bebone::gfx;

    class VulkanRendererTarget : public IRenderTarget {
        private:
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

        public:
            VulkanRenderTarget(const std::shared_ptr<VulkanSwapChain>& swap_chain);
            VulkanRendererTarget(const std::vector<std::shared_ptr<IAttachment>>& attachments, const Vec2i& viewport);
    };
}

#endif
