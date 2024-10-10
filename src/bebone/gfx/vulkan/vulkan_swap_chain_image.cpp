#include "vulkan_swap_chain_image.h"

#include "vulkan_device.h"

#include "vulkan_image.h"
#include "vulkan_image_view.h"
#include "vulkan_sampler.h"

namespace bebone::gfx {
    VulkanSwapChainImage::VulkanSwapChainImage(
            unique_ptr<VulkanImage>& image,
            unique_ptr<VulkanImageView>& view
    ) : image(std::move(image)), view(std::move(view))  {

    }

    VulkanSwapChainImage::~VulkanSwapChainImage() {
        LOG_DEBUG("Deleting vulkan swap chain image");
    }

    VkImage VulkanSwapChainImage::get_vulkan_image() const {
        return image->get_vulkan_image();
    }

    VkMemoryRequirements VulkanSwapChainImage::get_memory_requirements() const {
        return image->get_memory_requirements();
    }

    VkExtent3D VulkanSwapChainImage::get_extent() const {
        return image->get_extent();
    }

    VkImageView VulkanSwapChainImage::get_vulkan_image_view() const {
        return view->get_vulkan_image_view();
    }
}
