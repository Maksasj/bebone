#ifndef _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_
#define _BEBONE_GFX_VULKAN_IMAGE_TUPLE_H_

#include <vector>

#include "../gfx_backend.h"
#include "vulkan_image.h"

namespace bebone::gfx::vulkan {
        using namespace bebone::core;

        struct VulkanSwapChainImageTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanImageView> view;

            VulkanSwapChainImageTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanImageView>& view);

            void destroy(VulkanDevice &device) override;
        };

        struct VulkanDepthImageTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanImageView> view;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanDepthImageTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanImageView>& view,
                const shared_ptr<VulkanDeviceMemory>& memory);

            void destroy(VulkanDevice &device) override;
        };

        struct VulkanImageMemoryTuple : public VulkanApi {
            std::shared_ptr<VulkanImage> image;
            std::shared_ptr<VulkanDeviceMemory> memory;

            VulkanImageMemoryTuple(
                const shared_ptr<VulkanImage>& image,
                const shared_ptr<VulkanDeviceMemory>& memory);

            void destroy(VulkanDevice &device) override;
        };
}

#endif
