#ifndef _BEBONE_GFX_VULKAN_SWAP_CHAIN_IMAGE_H_
#define _BEBONE_GFX_VULKAN_SWAP_CHAIN_IMAGE_H_

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
            IVulkanDevice& device_owner;
            VkImage image;

            std::unique_ptr<VulkanImageView> view;

        public:
            VulkanSwapChainImage(IVulkanDevice& device, VkImage vk_image, VkFormat image_format);
            ~VulkanSwapChainImage();

            // Vulkan Image
            [[nodiscard]] VkImage get_vk_image() const override;
            [[nodiscard]] VkMemoryRequirements get_memory_requirements() const override;
            [[nodiscard]] VkExtent3D get_extent() const override;

            // Vulkan Image View
            [[nodiscard]] VkImageView get_vk_image_view() const override;
    };
}

#endif
