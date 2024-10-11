#ifndef _BEBONE_GFX_VULKAN_DEPTH_IMAGE_H_
#define _BEBONE_GFX_VULKAN_DEPTH_IMAGE_H_

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

    class VulkanDepthImage : public IVulkanImage, public IVulkanImageView {
        private:
            std::unique_ptr<VulkanImage> image;
            std::unique_ptr<VulkanImageView> view;
            std::unique_ptr<VulkanDeviceMemory> memory;

        public:
            VulkanDepthImage(VulkanDevice& device, VkExtent3D extent);

            VkImage get_vk_image() const override;
            VkMemoryRequirements get_memory_requirements() const override;
            VkExtent3D get_extent() const override;

            VkImageView get_vk_image_view() const override;
    };
}

#endif
