#include "vulkan_image_tuples.h"

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

        VkExtent3D VulkanSwapChainImage::get_extent() const {
            return image->get_extent();
        }

        VkImageView VulkanSwapChainImage::get_vulkan_image_view() const {
            return view->get_vulkan_image_view();
        }

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

        VkExtent3D VulkanDepthImage::get_extent() const {
            return image->get_extent();
        }

        VkImageView VulkanDepthImage::get_vulkan_image_view() const {
            return view->get_vulkan_image_view();
        }

        VulkanImageMemory::VulkanImageMemory(
            unique_ptr<VulkanImage>& image,
            unique_ptr<VulkanDeviceMemory>& memory
        ) : image(std::move(image)), memory(std::move(memory)) {

        }

        VkImage VulkanImageMemory::get_vulkan_image() const {
            return image->get_vulkan_image();
        }

        VkExtent3D VulkanImageMemory::get_extent() const {
            return image->get_extent();
        }
}
