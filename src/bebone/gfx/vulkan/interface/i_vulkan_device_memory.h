#ifndef _BEBONE_GFX_I_VULKAN_DEVICE_MEMORY_H_
#define _BEBONE_GFX_I_VULKAN_DEVICE_MEMORY_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanDeviceMemory {
        public:
            virtual VkDeviceMemory get_vk_device_memory() const = 0;
    };
}

#endif
