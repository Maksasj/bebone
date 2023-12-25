#ifndef _BEBONE_GFX_VULKAN_IMAGE_VIEW_H_
#define _BEBONE_GFX_VULKAN_IMAGE_VIEW_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanImage;

    class VulkanImageView : public VulkanWrapper<VkImageView>, private core::NonCopyable {
        public:
            VulkanImageView(VkImageView imageView);
            VulkanImageView(VulkanDevice& device, VulkanImage& image, VkFormat& imageFormat);

            static std::shared_ptr<VulkanImageView> create_default_depth_image_view(
                VulkanDevice &device,
                std::shared_ptr<VulkanImage>& image,
                VkFormat format);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
