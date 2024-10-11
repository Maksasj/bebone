#include "vulkan_depth_image.h"

#include "vulkan_image.h"
#include "vulkan_device.h"

namespace bebone::gfx {
    VulkanDepthImage::VulkanDepthImage(IVulkanDevice& device, VkExtent3D extent) {
        auto format = device.find_depth_format();

        VulkanImageInfo image_info{};
        image_info.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
        image = std::make_unique<VulkanImage>(device, format, extent, image_info);

        auto req = image->get_memory_requirements();

        memory = std::make_unique<VulkanDeviceMemory>(device, req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(image);

        VulkanImageViewInfo image_view_info{};
        image_view_info.subresource_range = { .aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT };
        view = std::make_unique<VulkanImageView>(device, *image, format, image_view_info);
    }

    VkImage VulkanDepthImage::get_vk_image() const {
        return image->get_vk_image();
    }

    VkMemoryRequirements VulkanDepthImage::get_memory_requirements() const {
        return image->get_memory_requirements();
    }

    VkExtent3D VulkanDepthImage::get_extent() const {
        return image->get_extent();
    }

    VkImageView VulkanDepthImage::get_vk_image_view() const {
        return view->get_vk_image_view();
    }
}
