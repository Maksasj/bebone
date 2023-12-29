#ifndef _BEBONE_GFX_VULKAN_VULKAN_IMAGE_H_
#define _BEBONE_GFX_VULKAN_VULKAN_IMAGE_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_device_memory.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    class VulkanDevice;

    class VulkanImage;
    class VulkanImageView;
    class VulkanDeviceMemory;

    struct VulkanSwapChainImageTuple {
        std::shared_ptr<VulkanImage> image;
        std::shared_ptr<VulkanImageView> view;
    };

    struct VulkanDepthImageTuple {
        std::shared_ptr<VulkanImage> image;
        std::shared_ptr<VulkanImageView> view;
        std::shared_ptr<VulkanDeviceMemory> memory;
    };

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

    class VulkanImage : public VulkanWrapper<VkImage>, private core::NonCopyable {
        public:
            VulkanImage(const VkImage& image);

            VulkanImage(
                VulkanDevice& device,
                VkFormat format,
                VkExtent3D extent,
                VulkanImageInfo imageInfo = {});

            VkMemoryRequirements get_memory_requirements(VulkanDevice& device);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
