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
            // Todo, generalize vulkan render target, get rid of VulkanSwapChainImageTuple
            std::vector<std::shared_ptr<VulkanSwapChainImageTuple>> color_attachments; // Todo, framebuffer can have multiple color_attachments
            std::vector<std::shared_ptr<VulkanDepthImageTuple>> depth_attachments;
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;

            // This is still just a swap chain render target constructor
            VulkanRenderTarget(
                VulkanDevice& device,
                std::shared_ptr<VulkanRenderPass>& render_pass,
                std::vector<std::shared_ptr<VulkanSwapChainImageTuple>>& attachments,
                VkExtent2D extent);

            void destroy(VulkanDevice& device);
    };
}

#endif
