#ifndef _BEBONE_GFX_VULKAN_IMAGE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_device_memory.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanCommandBufferPool;

    class VulkanImage;
    class VulkanImageView;
    class VulkanDeviceMemory;

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

    class VulkanImage : public VulkanWrapper<VkImage>, private core::NonCopyable {
        private:
            VkExtent3D extent;

        public:
            VulkanImage(const VkImage& image);

            // Todo save extent somewhere
            VulkanImage(
                VulkanDevice& device,
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo image_info = {});

            void transition_layout(
                VulkanDevice& device,
                VkImageLayout old_layout,
                VkImageLayout new_layout);

            VkExtent3D get_extent() const;

            VkMemoryRequirements get_memory_requirements(VulkanDevice& device);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
