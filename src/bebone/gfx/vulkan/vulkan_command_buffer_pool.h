#ifndef _BEBONE_GFX_VULKAN_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_VULKAN_COMMAND_BUFFER_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_device.h"

#include "interface/i_vulkan_command_buffer_pool.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanCommandBufferPool : public IVulkanCommandBufferPool, private core::NonCopyable {
        public:
            VkCommandPool command_buffer_pool;

        private:
            IVulkanDevice& device_owner;

        public:
            VulkanCommandBufferPool(IVulkanDevice& device);
            ~VulkanCommandBufferPool();

            std::unique_ptr<VulkanCommandBuffer> create_command_buffer();
            std::vector<std::unique_ptr<VulkanCommandBuffer>> create_command_buffers(const size_t& count);

            // Vulkan Command Buffer Pool
            VkCommandBuffer begin_single_time_commands() override;
            void end_single_time_commands(VkCommandBuffer command_buffer) override;
    };
}

#endif
