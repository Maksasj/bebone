#ifndef _BEBONE_GFX_VULKAN_RENDER_TARGET_H_
#define _BEBONE_GFX_VULKAN_RENDER_TARGET_H_

#include <array>

#include "../gfx_backend.h"

#include "vulkan_render_pass.h"
#include "vulkan_device.h"
#include "vulkan_image.h"
#include "vulkan_framebuffer.h"

namespace bebone::gfx {
    class VulkanImage;

    class VulkanRenderTarget : public VulkanApi {
        public:
            // FIF vector per multiple color attachments, for only one depth attachment possible
            vector<vector<shared_ptr<IVulkanAttachment>>> color_attachments;
            vector<shared_ptr<IVulkanAttachment>> depth_attachments;
            vector<shared_ptr<VulkanFramebuffer>> framebuffers;

            // This is still just a swap chain render target constructor
            VulkanRenderTarget(
                VulkanDevice& device,
                std::shared_ptr<VulkanRenderPass>& render_pass);

            VulkanRenderTarget(
                VulkanDevice& device,
                std::shared_ptr<VulkanRenderPass>& render_pass,
                std::vector<std::shared_ptr<VulkanSwapChainImageTuple>>& images);

            void destroy(VulkanDevice& device);
    };
}

#endif
