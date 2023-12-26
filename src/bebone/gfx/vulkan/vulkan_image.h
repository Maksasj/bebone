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

    class VulkanImage;
    class VulkanImageView;
    class VulkanDeviceMemory;

    struct VulkanSwapChainImageTuple {
        std::shared_ptr<VulkanImage> image;
        std::shared_ptr<VulkanImageView> view;
    };

    struct VulkanDepthImageTuple {
        std::shared_ptr<VulkanImage> image;
        std::shared_ptr<VulkanImageView> view;
        std::shared_ptr<VulkanDeviceMemory> memory;
    };

    class VulkanImage : public VulkanWrapper<VkImage>, private core::NonCopyable {
        public:
            VulkanImage(const VkImage& image);

            VulkanImage(
                VulkanDevice& device,
                const VkImageCreateInfo &imageInfo);

            VkMemoryRequirements get_memory_requirements(VulkanDevice& device);

            static std::shared_ptr<VulkanImage> create_default_depth_image(
                VulkanDevice& device,
                VkExtent2D extent,
                VkFormat format);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
