#ifndef _BEBONE_GFX_VULKAN_TEXTURE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_TEXTURE_TUPLE_H_

#include <vector>

#include "../gfx_backend.h"

#include "../../assets/image/image.h"

#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"
#include "vulkan_attachment.h"

namespace bebone::gfx {
    class VulkanDevice;

    using namespace bebone::core;

    class VulkanTexture : public IVulkanImage, public IVulkanImageView, public IVulkanSampler, private core::NonCopyable {
        private:
            std::unique_ptr<VulkanImage> image;
            std::unique_ptr<VulkanDeviceMemory> memory;
            std::unique_ptr<VulkanImageView> view;
            std::unique_ptr<VulkanSampler> sampler;

        public:
            VulkanTexture(
                VulkanDevice& device,
                const std::shared_ptr<assets::Image<ColorRGBA>>& raw);

            VulkanTexture(
                std::unique_ptr<VulkanImage>& image,
                std::unique_ptr<VulkanDeviceMemory>& memory,
                std::unique_ptr<VulkanImageView>& view,
                std::unique_ptr<VulkanSampler>& sampler);

            VulkanTexture(
                VulkanDevice& device,
                VkExtent3D extent,
                VkFormat image_format);

            VkImage get_vulkan_image() const override;
            VkImageView get_vulkan_image_view() const override;
            VkSampler get_vulkan_image_sampler() const override;
    };
}

#endif
