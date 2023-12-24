#ifndef _BEBONE_GFX_RENDER_TARGET_H_
#define _BEBONE_GFX_RENDER_TARGET_H_

#include <array>

#include "vulkan/vulkan_render_pass.h"

#include "vulkan/vulkan_device.h"
#include "gfx_backend.h"

namespace bebone::gfx {
    class RenderTarget {
        public:
            VulkanRenderPass renderPass;

            // Framebuffer things
            std::vector<VkFramebuffer> swapChainFramebuffers;
            
            std::vector<VkImage> depthImages;
            std::vector<VkDeviceMemory> depthImageMemorys;
            std::vector<VkImageView> depthImageViews;

            std::vector<VkImage> swapChainImages;
            std::vector<VkImageView> swapChainImageViews;
            VkFormat imageFormat;
            VkExtent2D extent;

            RenderTarget(VulkanDevice& _device, std::vector<VkImage>& _swapChainImages, VkFormat _imageFormat, VkExtent2D _extent);
            ~RenderTarget();

            void create_image_views(VulkanDevice& device);
            void create_framebuffers(VulkanDevice& device);
            void create_depth_resources(VulkanDevice& device);

            VkFormat find_depth_format(VulkanDevice& device);
    };
}

#endif
