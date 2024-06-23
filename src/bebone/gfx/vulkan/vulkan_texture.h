#ifndef _BEBONE_GFX_VULKAN_TEXTURE_H_
#define _BEBONE_GFX_VULKAN_TEXTURE_H_

#include <vector>

#include "../gfx_backend.h"

#include "../../assets/image/image.h"

#include "vulkan_image.h"
#include "vulkan_sampler.h"
#include "vulkan_image_view.h"

namespace bebone::gfx::vulkan {
    class VulkanDevice;

    using namespace bebone::core;

    struct VulkanTexture : public VulkanApi, private core::NonCopyable {
        std::shared_ptr<VulkanImage> image;
        std::shared_ptr<VulkanDeviceMemory> memory;
        std::shared_ptr<VulkanImageView> view;
        std::shared_ptr<VulkanSampler> sampler;

        public:
            VulkanTexture( // Constructors that require VulkanDevice& need to protected
                VulkanDevice& device,
                std::shared_ptr<VulkanCommandBufferPool>& commandBufferPool,
                const std::shared_ptr<assets::Image<ColorRGBA>>& raw);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
