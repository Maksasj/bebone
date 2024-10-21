#ifndef _BEBONE_GFX_VULKAN_IMAGE_VIEW_H_
#define _BEBONE_GFX_VULKAN_IMAGE_VIEW_H_

#include <vector>

#include "../gfx_backend.h"

#include "interface/i_vulkan_image_view.h"
#include "interface/i_vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanImage;

    struct VulkanImageSubresourceRange {
        VkImageAspectFlags aspect_mask = VK_IMAGE_ASPECT_COLOR_BIT;
        uint32_t base_mip_level = 0;
        uint32_t level_count = 1;
        uint32_t base_array_layer = 0;
        uint32_t layer_count = 1;
    };

    struct VulkanImageViewInfo {
        // VkStructureType type;
        // const void* ptr_next;
        VkImageViewCreateFlags flags = 0;
        // VkImage image;
        VkImageViewType view_type = VK_IMAGE_VIEW_TYPE_2D;
        // VkFormat format;
        VkComponentMapping components = {};
        VulkanImageSubresourceRange subresource_range = {};
    };

    class VulkanImageView : public IVulkanImageView, private core::NonCopyable {
        private:
            IVulkanDevice& device_owner;

            VkImageView image_view;

        public:
            VulkanImageView(IVulkanDevice& device, VulkanImage& image, const VkFormat& image_format, VulkanImageViewInfo image_view_info = {});
            VulkanImageView(IVulkanDevice& device, VkImage image, const VkFormat& image_format, VulkanImageViewInfo image_view_info = {});

            ~VulkanImageView() override;

            VkImageView get_vk_image_view() const override;
    };
}

#endif
