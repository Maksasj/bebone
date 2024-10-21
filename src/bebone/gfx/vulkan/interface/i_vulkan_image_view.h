#ifndef _BEBONE_GFX_I_VULKAN_IMAGE_VIEW_H_
#define _BEBONE_GFX_I_VULKAN_IMAGE_VIEW_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanImageView {
        public:
            virtual ~IVulkanImageView() = default;

            virtual VkImageView get_vk_image_view() const = 0;
    };
}

#endif
