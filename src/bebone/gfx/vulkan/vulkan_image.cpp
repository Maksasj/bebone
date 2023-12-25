#include "vulkan_image.h"

#include "vulkan_device.h"
#include "vulkan_image_view.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanImage::VulkanImage(const VkImage& image) {
        backend = image;
    }

    VulkanImage::VulkanImage(VulkanDevice& device, const VkImageCreateInfo &imageInfo) {
        if (vkCreateImage(device.device(), &imageInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }
    }

    VkMemoryRequirements VulkanImage::get_memory_requirements(VulkanDevice& device) {
        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device.device(), backend, &memRequirements);
        return memRequirements;
    }

    std::shared_ptr<VulkanImage> VulkanImage::create_default_depth_image(VulkanDevice& device, VkExtent2D extent, VkFormat format) {
        VkImageCreateInfo imageInfo{};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = extent.width;
        imageInfo.extent.height = extent.height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = 1;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        imageInfo.flags = 0;

        return std::make_shared<VulkanImage>(device, imageInfo);
    }

    void VulkanImage::destroy(bebone::gfx::VulkanDevice &device) {
        vkDestroyImage(device.device(), backend, nullptr);
    }
}
