#ifndef _BEBONE_GFX_VULKAN_SURFACE_H_
#define _BEBONE_GFX_VULKAN_SURFACE_H_

#include "../gfx_backend.h"

namespace bebone::gfx {
    class VulkanSurface {
        private:
            VkSurfaceKHR surface_;

        public:
            VulkanSurface();
    };
}

#endif
