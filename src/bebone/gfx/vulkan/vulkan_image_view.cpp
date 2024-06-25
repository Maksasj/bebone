#include "vulkan_image_view.h"

#include "vulkan_device.h"
#include "vulkan_image.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanImageView::VulkanImageView(VulkanDevice& device, VulkanImage& image, const VkFormat& imageFormat, VulkanImageViewInfo imageViewInfo) {
        VkImageViewCreateInfo createInfo{};

        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = imageViewInfo.flags;
        createInfo.image = image.backend;
        createInfo.viewType = imageViewInfo.viewType;
        createInfo.format = imageFormat;
        createInfo.components = imageViewInfo.components;

        createInfo.subresourceRange = {
            .aspectMask = imageViewInfo.subresourceRange.aspectMask,
            .baseMipLevel = imageViewInfo.subresourceRange.baseMipLevel,
            .levelCount = imageViewInfo.subresourceRange.levelCount,
            .baseArrayLayer = imageViewInfo.subresourceRange.baseArrayLayer,
            .layerCount = imageViewInfo.subresourceRange.layerCount
        };

        if (vkCreateImageView(device.device(), &createInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture image view!");
        }
    }

    void VulkanImageView::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyImageView(device.device(), backend, nullptr);

        mark_destroyed();
    }
}
