#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx {
    VulkanCommandBufferPool::VulkanCommandBufferPool(IVulkanDevice& device) : device_owner(device) {
        VulkanQueueFamilyIndices queue_family_indices = device.find_physical_queue_families();

        VkCommandPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        pool_info.queueFamilyIndex = queue_family_indices.graphics_family;
        pool_info.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT | VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

        if (vkCreateCommandPool(device_owner.get_vk_device(), &pool_info, nullptr, &command_buffer_pool) != VK_SUCCESS) {
            LOG_ERROR("Failed to create command pool");
            throw std::runtime_error("failed to create command pool!");
        }

        LOG_TRACE("Created command buffer pool");
    }

    VulkanCommandBufferPool::~VulkanCommandBufferPool() {
        device_owner.wait_idle();

        vkDestroyCommandPool(device_owner.get_vk_device(), command_buffer_pool, nullptr);

        LOG_TRACE("Destroyed command buffer pool");
    }

    std::unique_ptr<VulkanCommandBuffer> VulkanCommandBufferPool::create_command_buffer() {
        return std::make_unique<VulkanCommandBuffer>(device_owner, *this);
    }

    std::vector<std::unique_ptr<VulkanCommandBuffer>> VulkanCommandBufferPool::create_command_buffers(
        const size_t& count
    ) {
        auto command_buffers = std::vector<std::unique_ptr<VulkanCommandBuffer>> {};
        command_buffers.reserve(count);

        for(size_t i = 0; i < count; ++i)
            command_buffers.push_back(create_command_buffer());

        return command_buffers;
    }

    // Todo, rethink single time commands
    VkCommandBuffer VulkanCommandBufferPool::begin_single_time_commands() {
        VkCommandBufferAllocateInfo alloc_info{};

        alloc_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        alloc_info.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        alloc_info.commandPool = command_buffer_pool;
        alloc_info.commandBufferCount = 1;

        VkCommandBuffer command_buffer;
        vkAllocateCommandBuffers(device_owner.get_vk_device(), &alloc_info, &command_buffer);

        VkCommandBufferBeginInfo begin_info{};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

        vkBeginCommandBuffer(command_buffer, &begin_info);

        return command_buffer;
    }

    // Todo, rethink single time commands
    void VulkanCommandBufferPool::end_single_time_commands(VkCommandBuffer command_buffer) {
        vkEndCommandBuffer(command_buffer);

        VkSubmitInfo submit_info{};
        submit_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submit_info.commandBufferCount = 1;
        submit_info.pCommandBuffers = &command_buffer;

        vkQueueSubmit(device_owner.get_graphics_queue(), 1, &submit_info, VK_NULL_HANDLE);
        vkQueueWaitIdle(device_owner.get_graphics_queue());

        vkFreeCommandBuffers(device_owner.get_vk_device(), command_buffer_pool, 1, &command_buffer);
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
}
