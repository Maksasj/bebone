#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx {
    VulkanCommandBufferPool::VulkanCommandBufferPool(VulkanDevice& device) {
        QueueFamilyIndices queueFamilyIndices = device.find_physical_queue_families();

        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        if (vkCreateCommandPool(device.device(), &poolInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    std::vector<std::shared_ptr<VulkanCommandBuffer>> VulkanCommandBufferPool::create_command_buffers(std::shared_ptr<VulkanDevice>& device, const size_t& commandBufferCount) {
        std::vector<std::shared_ptr<VulkanCommandBuffer>> commandBuffersVector;

        for(size_t i = 0; i < commandBufferCount; ++i)
            commandBuffersVector.push_back(std::make_shared<VulkanCommandBuffer>(device, *this));

        return commandBuffersVector;
    }

    VkCommandBuffer VulkanCommandBufferPool::begin_single_time_commands(VulkanDevice& device) {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = backend;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer commandBuffer;
        vkAllocateCommandBuffers(device.device(), &allocInfo, &commandBuffer);

        VkCommandBufferBeginInfo beginInfo{};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(commandBuffer, &beginInfo);
        return commandBuffer;
    }

    void VulkanCommandBufferPool::end_single_time_commands(VulkanDevice& device, VkCommandBuffer commandBuffer) {
        vkEndCommandBuffer(commandBuffer);

        VkSubmitInfo submitInfo{};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &commandBuffer;

        vkQueueSubmit(device.graphicsQueue(), 1, &submitInfo, VK_NULL_HANDLE);
        vkQueueWaitIdle(device.graphicsQueue());

        vkFreeCommandBuffers(device.device(), backend, 1, &commandBuffer);
    }

    void VulkanCommandBufferPool::destroy(VulkanDevice& device) {
        vkDestroyCommandPool(device.device(), backend, nullptr);
    }


    // void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    //     VkCommandBuffer commandBuffer = begin_single_time_commands();
//
    //     VkBufferCopy copyRegion{};
    //     copyRegion.srcOffset = 0;  // Optional
    //     copyRegion.dstOffset = 0;  // Optional
    //     copyRegion.size = size;
    //     vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
//
    //     end_single_time_commands(commandBuffer);
    // }

    // void copy_buffe_to_image(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height, uint32_t layerCount) {
    //     VkCommandBuffer commandBuffer = begin_single_time_commands();
//
    //     VkBufferImageCopy region{};
    //     region.bufferOffset = 0;
    //     region.bufferRowLength = 0;
    //     region.bufferImageHeight = 0;
//
    //     region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    //     region.imageSubresource.mipLevel = 0;
    //     region.imageSubresource.baseArrayLayer = 0;
    //     region.imageSubresource.layerCount = layerCount;
//
    //     region.imageOffset = {0, 0, 0};
    //     region.imageExtent = {width, height, 1};
//
    //     vkCmdCopyBufferToImage(commandBuffer, buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
    //     end_single_time_commands(commandBuffer);
    // }
}
