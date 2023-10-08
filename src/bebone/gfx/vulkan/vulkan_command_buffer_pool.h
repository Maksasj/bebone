#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_device.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanCommandBufferPool {
        private:
            VulkanDevice& _device;

            VkCommandPool commandPool;
            core::ArenaContainer commandBuffers;

        public:
            VulkanCommandBufferPool(VulkanDevice& device, const size_t& commandBufferCount)
                : _device(device),
                  commandBuffers(sizeof(VulkanCommandBuffer) * commandBufferCount) {

                QueueFamilyIndices queueFamilyIndices = device.findPhysicalQueueFamilies();

                VkCommandPoolCreateInfo poolInfo = {};
                poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
                poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
                poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

                if (vkCreateCommandPool(device.device(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create command pool!");
                }

                for(size_t i = 0; i < commandBufferCount; ++i) {
                    VulkanCommandBuffer* commandBuffer = static_cast<VulkanCommandBuffer*>(commandBuffers.alloc(sizeof(VulkanCommandBuffer)));

                    if(commandBuffer == nullptr) {
                        throw std::runtime_error("failed to allocate vulkan command buffer");
                    }

                    std::ignore = new (commandBuffer) VulkanCommandBuffer(i);

                    VkCommandBufferAllocateInfo allocInfo{};
                    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                    allocInfo.commandPool = commandPool;
                    allocInfo.commandBufferCount = static_cast<uint32_t>(1);

                    if(vkAllocateCommandBuffers(device.device(), &allocInfo, &commandBuffer->commandBuffer) != VK_SUCCESS) {
                        throw std::runtime_error("Failed to allocate command buffers !");
                    }
                }
            }

            ~VulkanCommandBufferPool() {
                vkDestroyCommandPool(_device.device(), commandPool, nullptr);
            }

            VkCommandBuffer begin_single_time_commands() {
                VkCommandBufferAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
                allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
                allocInfo.commandPool = commandPool;
                allocInfo.commandBufferCount = 1;

                VkCommandBuffer commandBuffer;
                vkAllocateCommandBuffers(_device.device(), &allocInfo, &commandBuffer);

                VkCommandBufferBeginInfo beginInfo{};
                beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
                beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

                vkBeginCommandBuffer(commandBuffer, &beginInfo);
                return commandBuffer;
            }

            void end_single_time_commands(VkCommandBuffer commandBuffer) {
                vkEndCommandBuffer(commandBuffer);

                VkSubmitInfo submitInfo{};
                submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
                submitInfo.commandBufferCount = 1;
                submitInfo.pCommandBuffers = &commandBuffer;

                vkQueueSubmit(_device.graphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
                vkQueueWaitIdle(_device.graphicsQueue());

                vkFreeCommandBuffers(_device.device(), commandPool, 1, &commandBuffer);
            }

            void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
                VkCommandBuffer commandBuffer = begin_single_time_commands();

                VkBufferCopy copyRegion{};
                copyRegion.srcOffset = 0;  // Optional
                copyRegion.dstOffset = 0;  // Optional
                copyRegion.size = size;
                vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

                end_single_time_commands(commandBuffer);
            }

            void copy_buffe_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount) {
                VkCommandBuffer commandBuffer = begin_single_time_commands();

                VkBufferImageCopy region{};
                region.bufferOffset = 0;
                region.bufferRowLength = 0;
                region.bufferImageHeight = 0;

                region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                region.imageSubresource.mipLevel = 0;
                region.imageSubresource.baseArrayLayer = 0;
                region.imageSubresource.layerCount = layerCount;

                region.imageOffset = {0, 0, 0};
                region.imageExtent = {width, height, 1};

                vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
                end_single_time_commands(commandBuffer);
            }

            VulkanCommandBuffer& get_command_buffer(const size_t& index) {
                VulkanCommandBuffer* ptr = static_cast<VulkanCommandBuffer*>(commandBuffers.at(index));

                if(ptr == nullptr) {
                    throw std::runtime_error("Failed to retrive command buffer at index " + std::to_string(index));
                }

                return *ptr;
            }
    };  
}

#endif
