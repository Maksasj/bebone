#ifndef _BEBONE_GFX_VULKAN_IMAGE_VIEW_H_
#define _BEBONE_GFX_VULKAN_IMAGE_VIEW_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanImage;

    struct VulkanImageSubresourceRange {
        VkImageAspectFlags aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        uint32_t baseMipLevel = 0;
        uint32_t levelCount = 1;
        uint32_t baseArrayLayer = 0;
        uint32_t layerCount = 1;
    };

    struct VulkanImageViewInfo {
        // VkStructureType sType;
        // const void* pNext;
        VkImageViewCreateFlags flags = 0;
        // VkImage image;
        VkImageViewType viewType = VK_IMAGE_VIEW_TYPE_2D;
        // VkFormat format;
        VkComponentMapping components = {};
        VulkanImageSubresourceRange subresourceRange = {};
    };

    class VulkanImageView : public VulkanWrapper<VkImageView>, private core::NonCopyable {
        public:
            VulkanImageView(
                VulkanDevice& device,
                VulkanImage& image,
                VkFormat& imageFormat,
                VulkanImageViewInfo imageViewInfo = {});

            void destroy(VulkanDevice &device) override;
    };
}

#endif
