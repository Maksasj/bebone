#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx::vulkan {
    VulkanCommandBufferPool::VulkanCommandBufferPool(VulkanDevice& device) {
        QueueFamilyIndices queue_family_indices = device.find_physical_queue_families();

        VkCommandPoolCreateInfo pool_info = {};
        pool_info.type = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_info.queueFamilyIndex = queue_family_indices.graphics_family;
        pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        if (vkCreateCommandPool(device.device, &pool_info, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create command pool!");
        }
    }

    std::vector<std::shared_ptr<VulkanCommandBuffer>> VulkanCommandBufferPool::create_command_buffers(
        std::shared_ptr<VulkanDevice>& device,
        const size_t& count
    ) {
        auto command_buffers = std::vector<std::shared_ptr<VulkanCommandBuffer>> {};
        command_buffers.reserve(count);

        for(size_t i = 0; i < count; ++i)
            command_buffers.push_back(std::make_shared<VulkanCommandBuffer>(device, *this));

        return command_buffers;
    }

    // Todo, rethink single time commands
    VkCommandBuffer VulkanCommandBufferPool::begin_single_time_commands(VulkanDevice& device) {
        VkCommandBufferAllocateInfo alloc_info{};

        alloc_info.type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandPool = backend;
        alloc_info.command_bufferCount = 1;

        VkCommandBuffer command_buffer;
        vkAllocateCommandBuffers(device.device, &alloc_info, &command_buffer);

        VkCommandBufferBeginInfo begin_info{};
        begin_info.type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(command_buffer, &begin_info);

        return command_buffer;
    }

    // Todo, rethink single time commands
    void VulkanCommandBufferPool::end_single_time_commands(VulkanDevice& device, VkCommandBuffer command_buffer) {
        vkEndCommandBuffer(command_buffer);

        VkSubmitInfo submit_info{};
        submit_info.type = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.command_bufferCount = 1;
        submit_info.pCommandBuffers = &command_buffer;

        vkQueueSubmit(device.graphics_queue, 1, &submit_info, VK_NULL_HANDLE);
        vkQueueWaitIdle(device.graphics_queue);

        vkFreeCommandBuffers(device.device, backend, 1, &command_buffer);
    }

    void VulkanCommandBufferPool::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyCommandPool(device.device, backend, nullptr);

        mark_destroyed();
    }


    // void copy_buffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
    //     VkCommandBuffer command_buffer = begin_single_time_commands();
//
    //     VkBufferCopy copyRegion{};
    //     copyRegion.srcOffset = 0;  // Optional
    //     copyRegion.dstOffset = 0;  // Optional
    //     copyRegion.size = size;
    //     vkCmdCopyBuffer(command_buffer, srcBuffer, dstBuffer, 1, &copyRegion);
//
    //     end_single_time_commands(command_buffer);
    // }

    void VulkanCommandBufferPool::copy_buffer_to_image(
        VulkanDevice& device,
        const std::shared_ptr<VulkanBuffer>& buffer,
        const std::shared_ptr<VulkanImage>& image,
        const u32& width,
        const u32& height,
        const u32& layer_count
    ) {
        VkCommandBuffer command_buffer = begin_single_time_commands(device);

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;

        region.imageSubresource.aspect_mask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.base_array_layer = 0;
        region.imageSubresource.layer_count = layer_count;

        region.imageOffset = {0, 0, 0};
        region.imageExtent = {width, height, 1};

        vkCmdCopyBufferToImage(command_buffer, buffer->backend, image->backend, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);
        end_single_time_commands(device, command_buffer);
    }
}
