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
            // Vector of all FIFO attachments
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

            vector<shared_ptr<IVulkanAttachment>>& get_color_attachment(const size_t& index);
            vector<shared_ptr<IVulkanAttachment>>& depth_attachment();

            // void destroy(VulkanDevice& device);
    };
}

#endif
