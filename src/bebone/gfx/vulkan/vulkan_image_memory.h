#ifndef _BEBONE_GFX_VULKAN_IMAGE_MEMORY_H_
#define _BEBONE_GFX_VULKAN_IMAGE_MEMORY_H_

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

    struct VulkanImageMemory : public IVulkanImage {
        std::unique_ptr<VulkanImage> image;
        std::unique_ptr<VulkanDeviceMemory> memory;

    public:
        VulkanImageMemory(unique_ptr<VulkanImage>& image, unique_ptr<VulkanDeviceMemory>& memory);

        VkImage get_vulkan_image() const override;
        VkMemoryRequirements get_memory_requirements() const override;
        VkExtent3D get_extent() const override;
    };
}

#endif
