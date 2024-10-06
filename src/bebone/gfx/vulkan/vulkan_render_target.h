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
            vector<vector<unique_ptr<IVulkanAttachment>>> color_attachments;
            vector<unique_ptr<IVulkanAttachment>> depth_attachments;
            vector<unique_ptr<VulkanFramebuffer>> framebuffers;

            // This is still just a swap chain render target constructor
            VulkanRenderTarget(
                VulkanDevice& device,
                std::unique_ptr<VulkanRenderPass>& render_pass);

            VulkanRenderTarget(
                VulkanDevice& device,
                std::unique_ptr<VulkanRenderPass>& render_pass,
                std::vector<std::unique_ptr<VulkanSwapChainImageTuple>>& images);

            ~VulkanRenderTarget();

            vector<unique_ptr<IVulkanAttachment>>& get_color_attachment(const size_t& index);
            vector<unique_ptr<IVulkanAttachment>>& depth_attachment();

            // void destroy(VulkanDevice& device);
    };
}

#endif
