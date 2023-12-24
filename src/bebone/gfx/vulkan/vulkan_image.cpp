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

    void VulkanImage::create_image_view(VulkanDevice& device, VkFormat& imageFormat) {
        imageView = std::make_shared<VulkanImageView>(device, *this, imageFormat);
    }

    void VulkanImage::destroy(bebone::gfx::VulkanDevice &device) {
        vkDestroyImage(device.device(), backend, nullptr);

        if(imageView != nullptr)
            imageView->destroy(device);

        if(imageMemory != nullptr)
            imageMemory->destroy(device);
    }
}
