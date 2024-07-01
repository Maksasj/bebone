#ifndef _BEBONE_GFX_VULKAN_RENDER_TARGET_H_
#define _BEBONE_GFX_VULKAN_RENDER_TARGET_H_

#include <array>

#include "../gfx_backend.h"

#include "vulkan_render_pass.h"
#include "vulkan_device.h"
#include "vulkan_image.h"
#include "vulkan_framebuffer.h"

namespace bebone::gfx::vulkan {
    class VulkanImage;

    class VulkanRenderTarget : public VulkanApi {
        public:
            std::shared_ptr<VulkanRenderPass> render_pass; // Todo, why this is there ?

            std::vector<std::shared_ptr<VulkanFramebuffer>> swap_chain_framebuffers;
            std::vector<VulkanDepthImageTuple> depth_images;
            std::vector<VulkanSwapChainImageTuple> swap_chain_images;

            VulkanRenderTarget(
                VulkanDevice& device,
                std::vector<VulkanSwapChainImageTuple>& swap_chain_images,
                VkFormat image_format,
                VkExtent2D extent);

            void destroy(VulkanDevice& device);
    };
}

#endif
