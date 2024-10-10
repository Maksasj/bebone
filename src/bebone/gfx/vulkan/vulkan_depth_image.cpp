#include "vulkan_depth_image.h"

#include "vulkan_device.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_sampler.h"

namespace bebone::gfx {
    VulkanDepthImage::VulkanDepthImage(VulkanDevice& device, VkExtent3D extent) {
        auto format = device.find_depth_format();

        image = device.create_image(format, extent, {
                .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
        });

        auto req = image->get_memory_requirements();

        memory = device.create_device_memory(req, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
        memory->bind_image_memory(image);

        view = device.create_image_view(*image, format, {
                .subresource_range = { .aspect_mask = VK_IMAGE_ASPECT_DEPTH_BIT },
        });
    }

    VkImage VulkanDepthImage::get_vulkan_image() const {
        return image->get_vulkan_image();
    }

    VkMemoryRequirements VulkanDepthImage::get_memory_requirements() const {
        return image->get_memory_requirements();
    }

    VkExtent3D VulkanDepthImage::get_extent() const {
        return image->get_extent();
    }

    VkImageView VulkanDepthImage::get_vulkan_image_view() const {
        return view->get_vulkan_image_view();
    }
}
