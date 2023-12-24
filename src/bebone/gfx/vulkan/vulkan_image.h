#ifndef _BEBONE_GFX_VULKAN_IMAGE_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_IMAGE_IMPLEMENTATION_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_device_memory.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanImageView;

    class VulkanImage : public VulkanWrapper<VkImage>, private core::NonCopyable {
        public:
            std::shared_ptr<VulkanImageView> imageView;
            std::shared_ptr<VulkanDeviceMemory> imageMemory;

            VulkanImage(const VkImage& image);
            VulkanImage(VulkanDevice& device, const VkImageCreateInfo &imageInfo);

            // Todo not sure if this is should be there;
            void create_image_view(VulkanDevice& device, VkFormat& imageFormat);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
