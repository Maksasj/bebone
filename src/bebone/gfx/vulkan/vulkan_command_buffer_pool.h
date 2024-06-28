#ifndef _BEBONE_GFX_VULKAN_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_VULKAN_COMMAND_BUFFER_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_device.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx::vulkan {
    class VulkanCommandBufferPool : public VulkanWrapper<VkCommandPool>, private core::NonCopyable {
        public:
            VulkanCommandBufferPool(VulkanDevice& device);

            std::vector<std::shared_ptr<VulkanCommandBuffer>> create_command_buffers(
                std::shared_ptr<VulkanDevice>& device,
                const size_t& count);

            // Todo, refactor this
            VkCommandBuffer begin_single_time_commands(VulkanDevice& device);
            void end_single_time_commands(VulkanDevice& device, VkCommandBuffer command_buffer);

            // Wait why copy buffer to image is in VulkanCommandBufferPool class ?
            void copy_buffer_to_image(VulkanDevice& device, std::shared_ptr<VulkanBuffer> buffer, std::shared_ptr<VulkanImage> image);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
