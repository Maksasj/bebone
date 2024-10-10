#ifndef _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_

#include <memory>

#include "../gfx_backend.h"

#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"

#include "interface/i_vulkan_image.h"
#include "interface/i_vulkan_image_view.h"
#include "interface/i_vulkan_sampler.h"

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
            VkExtent3D get_extent() const override;

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
            VkExtent3D get_extent() const override;

            VkImageView get_vulkan_image_view() const override;
    };

    struct VulkanImageMemory : public IVulkanImage {
            std::unique_ptr<VulkanImage> image;
            std::unique_ptr<VulkanDeviceMemory> memory;

        public:
            VulkanImageMemory(unique_ptr<VulkanImage>& image, unique_ptr<VulkanDeviceMemory>& memory);

            VkImage get_vulkan_image() const override;
            VkExtent3D get_extent() const override;
    };
}

#endif
