#ifndef _BEBONE_GFX_VULKAN_VULKAN_RENDER_TARGET_H_
#define _BEBONE_GFX_VULKAN_VULKAN_RENDER_TARGET_H_

#include <array>

#include "../gfx_backend.h"

#include "vulkan_render_pass.h"
#include "vulkan_device.h"
#include "vulkan_image.h"
#include "vulkan_framebuffer.h"

namespace bebone::gfx::vulkan {
    class VulkanImage;

    class VulkanRenderTarget {
        public:
            std::shared_ptr<VulkanRenderPass> renderPass;

            std::vector<std::shared_ptr<VulkanFramebuffer>> swapChainFramebuffers;
            std::vector<VulkanDepthImageTuple> depthImages;
            std::vector<VulkanSwapChainImageTuple> swapChainImages;

            VulkanRenderTarget(
                VulkanDevice& device,
                std::vector<VulkanSwapChainImageTuple>& swapChainImages,
                VkFormat imageFormat,
                VkExtent2D extent);

            void destroy(VulkanDevice& device);
    };
}

#endif
