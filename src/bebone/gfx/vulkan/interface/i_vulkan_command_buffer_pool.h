#ifndef _BEBONE_GFX_I_VULKAN_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_I_VULKAN_COMMAND_BUFFER_POOL_H_

#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class IVulkanCommandBufferPool {
        virtual VkCommandBuffer begin_single_time_commands() = 0;
        virtual void end_single_time_commands(VkCommandBuffer command_buffer) = 0;
    };
}

#endif
