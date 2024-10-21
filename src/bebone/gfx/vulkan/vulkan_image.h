#ifndef _BEBONE_GFX_VULKAN_IMAGE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_H_

#include <vector>

#include "../gfx_backend.h"

#include "interface/i_vulkan_image.h"
#include "interface/i_vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    struct VulkanImageInfo {
        // VkStructureType type;
        // const void* ptr_next;
        VkImageCreateFlags flags = 0;
        VkImageType image_type = VK_IMAGE_TYPE_2D;
        // VkFormat format = VK_FORMAT_UNDEFINED;
        // VkExtent3D extent = {0, 0, 0};
        uint32_t mip_levels = 1;
        uint32_t array_layers = 1;
        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
        VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
        VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        VkSharingMode sharing_mode = VK_SHARING_MODE_EXCLUSIVE;
        uint32_t queue_family_index_count = 0;
        const uint32_t* ptr_queue_family_indices = nullptr;
        VkImageLayout initial_layout = VK_IMAGE_LAYOUT_UNDEFINED;
    };

    class VulkanImage : public IVulkanImage, private core::NonCopyable {
        private:
            IVulkanDevice& device_owner;
            VkImage image;
            VkExtent3D extent;

        public:
            VulkanImage(IVulkanDevice& device, VkFormat format, VkExtent3D extent, VulkanImageInfo image_info = {});
            ~VulkanImage();

            void transition_layout(VkImageLayout old_layout, VkImageLayout new_layout);

            [[nodiscard]] VkImage get_vk_image() const override;
            [[nodiscard]] VkMemoryRequirements get_memory_requirements() const override;
            [[nodiscard]] VkExtent3D get_extent() const override;
    };
}

#endif
