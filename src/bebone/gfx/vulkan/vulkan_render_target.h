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

    class VulkanRenderTarget {
        public:
            // Vector of all FIFO attachments
            vector<vector<unique_ptr<IVulkanImageView>>> color_attachments;
            vector<unique_ptr<IVulkanImageView>> depth_attachments;
            vector<unique_ptr<VulkanFramebuffer>> framebuffers;

            // This is still just a swap chain render target constructor
            VulkanRenderTarget(
                IVulkanDevice& device,
                std::unique_ptr<VulkanRenderPass>& render_pass);

            VulkanRenderTarget(
                IVulkanDevice& device,
                std::unique_ptr<VulkanRenderPass>& render_pass,
                std::vector<std::unique_ptr<VulkanSwapChainImage>>& images);

            ~VulkanRenderTarget();
    };
}

#endif
