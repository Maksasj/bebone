#ifndef _BEBONE_GFX_VULKAN_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_VULKAN_COMMAND_BUFFER_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_device.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanCommandBufferPool : private core::NonCopyable {
        public:
            VkCommandPool backend;

        private:
            VulkanDevice& device_owner;

        public:
            VulkanCommandBufferPool(VulkanDevice& device);
            ~VulkanCommandBufferPool();

            std::unique_ptr<VulkanCommandBuffer> create_command_buffer();
            std::vector<std::unique_ptr<VulkanCommandBuffer>> create_command_buffers(const size_t& count);

            // Todo, refactor this
            VkCommandBuffer begin_single_time_commands();
            void end_single_time_commands(VkCommandBuffer command_buffer);
    };
}

#endif
