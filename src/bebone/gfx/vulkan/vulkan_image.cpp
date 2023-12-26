#include "vulkan_image.h"

#include "vulkan_device.h"
#include "vulkan_image_view.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanImage::VulkanImage(const VkImage& image) {
        backend = image;
    }

    VulkanImage::VulkanImage(VulkanDevice& device, VulkanImageInfo imageInfo) {
        VkImageCreateInfo createInfo{};

        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = imageInfo.flags;
        createInfo.imageType = imageInfo.imageType;
        createInfo.format = imageInfo.format;
        createInfo.extent = imageInfo.extent;
        createInfo.mipLevels = imageInfo.mipLevels;
        createInfo.arrayLayers = imageInfo.arrayLayers;
        createInfo.samples = imageInfo.samples;
        createInfo.tiling = imageInfo.tiling;
        createInfo.usage = imageInfo.usage;
        createInfo.sharingMode = imageInfo.sharingMode;
        createInfo.queueFamilyIndexCount = imageInfo.queueFamilyIndexCount;
        createInfo.pQueueFamilyIndices = imageInfo.pQueueFamilyIndices;
        createInfo.initialLayout = imageInfo.initialLayout;

        if (vkCreateImage(device.device(), &createInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }
    }

    VkMemoryRequirements VulkanImage::get_memory_requirements(VulkanDevice& device) {
        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device.device(), backend, &memRequirements);
        return memRequirements;
    }

    void VulkanImage::destroy(bebone::gfx::VulkanDevice &device) {
        vkDestroyImage(device.device(), backend, nullptr);
    }
}
