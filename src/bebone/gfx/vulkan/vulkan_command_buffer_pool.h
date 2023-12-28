#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_device.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanCommandBufferPool : public VulkanWrapper<VkCommandPool>, private core::NonCopyable {
        public:
            VulkanCommandBufferPool(VulkanDevice& device);

            std::vector<std::shared_ptr<VulkanCommandBuffer>> create_command_buffers(std::shared_ptr<VulkanDevice>& device, const size_t& commandBufferCount);

            VkCommandBuffer begin_single_time_commands(VulkanDevice& device);
            void end_single_time_commands(VulkanDevice& device, VkCommandBuffer commandBuffer);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
