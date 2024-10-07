#ifndef _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_

#include <vector>

#include "../gfx_backend.h"
#include "vulkan_image.h"
#include "vulkan_attachment.h"

namespace bebone::gfx {
    using namespace bebone::core;

    struct VulkanSwapChainImage : public IVulkanImage, public IVulkanImageView {
        private:
            std::unique_ptr<VulkanImage> image;
            std::unique_ptr<VulkanImageView> view;

        public:
            VulkanSwapChainImage(unique_ptr<VulkanImage>& image, unique_ptr<VulkanImageView>& view);
            ~VulkanSwapChainImage();

            VkImage get_vulkan_image() const override;
            VkImageView get_vulkan_image_view() const override;
        };

    class VulkanDepthImage : public IVulkanImage, public IVulkanImageView {
        private:
            std::unique_ptr<VulkanImage> image;
            std::unique_ptr<VulkanImageView> view;
            std::unique_ptr<VulkanDeviceMemory> memory;

        public:
            VulkanDepthImage(VulkanDevice& device, VkExtent3D extent);

            VkImage get_vulkan_image() const override;
            VkImageView get_vulkan_image_view() const override;
    };

    struct VulkanImageMemory : public IVulkanImage {
            std::unique_ptr<VulkanImage> image;
            std::unique_ptr<VulkanDeviceMemory> memory;

        public:
            VulkanImageMemory(unique_ptr<VulkanImage>& image, unique_ptr<VulkanDeviceMemory>& memory);

            VkImage get_vulkan_image() const override;
    };
}

#endif
