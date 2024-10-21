#include "vulkan_image_memory.h"

#include "vulkan_device.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_sampler.h"

namespace bebone::gfx {
    VulkanImageMemory::VulkanImageMemory(
            unique_ptr<VulkanImage>& image,
            unique_ptr<VulkanDeviceMemory>& memory
    ) : image(std::move(image)), memory(std::move(memory)) {

    }

    VulkanImageMemory::~VulkanImageMemory() = default;

    VkImage VulkanImageMemory::get_vk_image() const {
        return image->get_vk_image();
    }

    VkMemoryRequirements VulkanImageMemory::get_memory_requirements() const {
        return image->get_memory_requirements();
    }

    VkExtent3D VulkanImageMemory::get_extent() const {
        return image->get_extent();
    }
}
