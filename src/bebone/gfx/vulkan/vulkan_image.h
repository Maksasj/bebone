#ifndef _BEBONE_GFX_VULKAN_IMAGE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_device_memory.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanCommandBufferPool;

    class VulkanImage;
    class VulkanImageView;
    class VulkanDeviceMemory;

    using VulkanSwapChainImageTuple = std::tuple<std::shared_ptr<VulkanImage>, std::shared_ptr<VulkanImageView>>;
    using VulkanDepthImageTuple = std::tuple<std::shared_ptr<VulkanImage>, std::shared_ptr<VulkanImageView>, std::shared_ptr<VulkanDeviceMemory>>;

    struct VulkanImageInfo {
        // VkStructureType sType;
        // const void* pNext;
        VkImageCreateFlags flags = 0;
        VkImageType imageType = VK_IMAGE_TYPE_2D;
        // VkFormat format = VK_FORMAT_UNDEFINED;
        // VkExtent3D extent = {0, 0, 0};
        uint32_t mipLevels = 1;
        uint32_t arrayLayers = 1;
        VkSampleCountFlagBits samples = VK_SAMPLE_COUNT_1_BIT;
        VkImageTiling tiling = VK_IMAGE_TILING_OPTIMAL;
        VkImageUsageFlags usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        uint32_t queueFamilyIndexCount = 0;
        const uint32_t* pQueueFamilyIndices = nullptr;
        VkImageLayout initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    };

    using VulkanImageMemoryTuple = std::tuple<std::shared_ptr<VulkanImage>, std::shared_ptr<VulkanDeviceMemory>>;

    class VulkanImage : public VulkanWrapper<VkImage>, private core::NonCopyable {
        public:
            VulkanImage(const VkImage& image);

            VulkanImage(
                VulkanDevice& device,
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo imageInfo = {});

            void transition_layout(
                VulkanCommandBufferPool& pool,
                VulkanDevice& device,
                VkImageLayout oldLayout,
                VkImageLayout newLayout);

            VkMemoryRequirements get_memory_requirements(VulkanDevice& device);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
