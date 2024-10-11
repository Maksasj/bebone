#include "vulkan_swap_chain_image.h"

#include "vulkan_device.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_sampler.h"

namespace bebone::gfx {
    VulkanSwapChainImage::VulkanSwapChainImage(
        IVulkanDevice& device,
        VkImage vk_image,
        VkFormat image_format
    ) : device_owner(device), image(vk_image) {
        VulkanImageViewInfo image_view_info{};
        view = std::make_unique<VulkanImageView>(device, image, image_format, image_view_info);
    }

    VulkanSwapChainImage::~VulkanSwapChainImage() {
        LOG_DEBUG("Deleting vulkan swap chain image");
        view.reset();
    }

    VkImage VulkanSwapChainImage::get_vk_image() const {
        return image;
    }

    VkMemoryRequirements VulkanSwapChainImage::get_memory_requirements() const {
        VkMemoryRequirements requirements;

        vkGetImageMemoryRequirements(device_owner.get_vk_device(), image, &requirements);

        return requirements;
    }

    VkExtent3D VulkanSwapChainImage::get_extent() const {
        LOG_CRITICAL("IVulkanImage::get_extent() is not implemented for VulkanSwapChainImage class");
        return VkExtent3D { 0u, 0u, 0u };
    }

    VkImageView VulkanSwapChainImage::get_vk_image_view() const {
        return view->get_vk_image_view();
    }
}
