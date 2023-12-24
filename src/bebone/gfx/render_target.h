#ifndef _BEBONE_GFX_RENDER_TARGET_H_
#define _BEBONE_GFX_RENDER_TARGET_H_

#include <array>

#include "vulkan/vulkan_render_pass.h"

#include "vulkan/vulkan_device.h"
#include "gfx_backend.h"

namespace bebone::gfx {
    class VulkanImage;

    class RenderTarget {
        public:
            VulkanRenderPass renderPass;

            // Framebuffer things
            std::vector<VkFramebuffer> swapChainFramebuffers;
            
            std::vector<VkImage> depthImages;
            std::vector<VkImageView> depthImageViews;
            std::vector<VkDeviceMemory> depthImageMemorys;

            // Not sure do we need to store image views and device memory inside VulkanImage class
            std::vector<std::shared_ptr<VulkanImage>> swapChainImages;

            VkFormat imageFormat;
            VkExtent2D extent;

            RenderTarget(VulkanDevice& _device, std::vector<std::shared_ptr<VulkanImage>>& _swapChainImages, VkFormat _imageFormat, VkExtent2D _extent);

            void create_framebuffers(VulkanDevice& device);
            void create_depth_resources(VulkanDevice& device);

            void destroy(VulkanDevice& device);
    };
}

#endif
