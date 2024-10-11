#ifndef _BEBONE_GFX_I_VULKAN_IMAGE_H_
#define _BEBONE_GFX_I_VULKAN_IMAGE_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanImage {
        public:
            virtual VkImage get_vk_image() const = 0;
            virtual VkMemoryRequirements get_memory_requirements() const = 0;
            virtual VkExtent3D get_extent() const = 0;
    };
}

#endif
