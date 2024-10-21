#ifndef _BEBONE_GFX_I_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_I_VULKAN_COMMAND_BUFFER_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanCommandBuffer {
        private:
        public:
            virtual ~IVulkanCommandBuffer() = default;
    };
}

#endif
