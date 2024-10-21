#ifndef _BEBONE_GFX_VULKAN_TEXTURE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_TEXTURE_TUPLE_H_

#include <vector>

#include "../gfx_backend.h"

#include "../../assets/image/image.h"

#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"

#include "interface/i_vulkan_image.h"
#include "interface/i_vulkan_image_view.h"
#include "interface/i_vulkan_sampler.h"

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
            VulkanTexture(IVulkanDevice& device, const std::shared_ptr<assets::Image<ColorRGBA>>& raw);
            VulkanTexture(IVulkanDevice& device, VkExtent3D extent, VkFormat image_format);
            ~VulkanTexture() override;

            // Vulkan Image
            [[nodiscard]] VkImage get_vk_image() const override;
            [[nodiscard]] VkMemoryRequirements get_memory_requirements() const override;
            [[nodiscard]] VkExtent3D get_extent() const override;

            // Vulkan Image View
            [[nodiscard]] VkImageView get_vk_image_view() const override;

            // Vulkan Sampler
            [[nodiscard]] VkSampler get_vk_image_sampler() const override;
    };
}

#endif
