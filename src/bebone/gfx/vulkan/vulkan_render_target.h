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

    // Todo
    class VulkanRenderTarget : public VulkanApi {
        public:
            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;
            std::vector<std::shared_ptr<VulkanTexture>> color_attachments;
            std::vector<VulkanDepthImageTuple> depth_attachments;
    };

    class VulkanSwapChainRenderTarget : public VulkanApi {
        public:
            std::shared_ptr<VulkanRenderPass> render_pass; // Todo, why this is there ?

            std::vector<std::shared_ptr<VulkanFramebuffer>> framebuffers;
            std::vector<VulkanDepthImageTuple> depth_images;
            std::vector<VulkanSwapChainImageTuple> image_views;

            VulkanSwapChainRenderTarget(
                VulkanDevice& device,
                std::vector<VulkanSwapChainImageTuple>& image_views,
                VkFormat image_format,
                VkExtent2D extent);

            void destroy(VulkanDevice& device);
    };
}

#endif
