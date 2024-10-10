#include "vulkan_image_view.h"

#include "vulkan_device.h"
#include "vulkan_image.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanImageView::VulkanImageView(VulkanDevice& device, VulkanImage& image, const VkFormat& image_format, VulkanImageViewInfo image_view_info) : device_owner(device) {
        VkImageViewCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        create_info.pNext = nullptr;
        create_info.flags = image_view_info.flags;
        create_info.image = image.get_vulkan_image();
        create_info.viewType = image_view_info.view_type;
        create_info.format = image_format;
        create_info.components = image_view_info.components;

        create_info.subresourceRange = {
            .aspectMask = image_view_info.subresource_range.aspect_mask,
            .baseMipLevel = image_view_info.subresource_range.base_mip_level,
            .levelCount = image_view_info.subresource_range.level_count,
            .baseArrayLayer = image_view_info.subresource_range.base_array_layer,
            .layerCount = image_view_info.subresource_range.layer_count
        };

        if(vkCreateImageView(device.device, &create_info, nullptr, &image_view) != VK_SUCCESS) {
            LOG_ERROR("Failed to create texture image view");
            throw std::runtime_error("failed to create texture image view!");
        }

        LOG_TRACE("Created Vulkan image view");
    }

    VulkanImageView::~VulkanImageView() {
        // vkDestroyImageView(device_owner.device, backend, nullptr);

        LOG_DEBUG("Destroyed Vulkan image view");
    }

    VkImageView  VulkanImageView::get_vulkan_image_view() const {
        return image_view;
    }
}
