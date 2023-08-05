#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_POOL_H_

#include <vector>

#include "../gfx_backend.h"
#include "../command_buffer_pool.h"

#include "../../client/device.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanCommandBufferPool : public CommandBufferPool {
        private:
            std::vector<VulkanCommandBuffer> commandBuffers;
            
        public:
            VulkanCommandBufferPool(const MyEngineDevice& device, const size_t& commandBufferCount) {
                for(size_t i = 0; i < commandBufferCount; ++i) {
                    commandBuffers.push_back(VulkanCommandBuffer());

                    VkCommandBufferAllocateInfo allocInfo{};
                    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                    allocInfo.commandPool = device.getCommandPool();
                    allocInfo.commandBufferCount = static_cast<uint32_t>(1);

                    if(vkAllocateCommandBuffers(device.device(), &allocInfo, &commandBuffers[0].commandBuffer) != VK_SUCCESS) {
                        throw std::runtime_error("Failed to allocate command buffers !");
                    }
                }
            }

            CommandBuffer& get_command_buffer(const size_t& commandBufferIndex) override {
                return commandBuffers[commandBufferIndex];
            }
    };  
}

#endif
