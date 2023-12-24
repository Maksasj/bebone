#include "vulkan_image_view.h"

#include "vulkan_device.h"
#include "vulkan_image.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanImageView::VulkanImageView(VulkanDevice& device, VulkanImage& image, VkFormat& imageFormat) {
        VkImageViewCreateInfo viewInfo{};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image.backend;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = imageFormat;
        viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = 1;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        if (vkCreateImageView(device.device(), &viewInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture image view!");
        }
    }

    void VulkanImageView::destroy(bebone::gfx::VulkanDevice &device) {
        vkDestroyImageView(device.device(), backend, nullptr);
    }
}
