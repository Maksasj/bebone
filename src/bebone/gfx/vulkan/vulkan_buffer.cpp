#include "vulkan_buffer.h"

#include "vulkan_device.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanBuffer::VulkanBuffer(VulkanDevice& device, VkDeviceSize size, VulkanBufferInfo buffer_info) {//VkMemoryPropertyFlags properties) {
        VkBufferCreateInfo createInfo{};

        createInfo.type = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        createInfo.ptr_next = nullptr;
        createInfo.flags = buffer_info.flags;
        createInfo.size = size;
        createInfo.usage = buffer_info.usage;
        createInfo.sharingMode = buffer_info.sharingMode;
        createInfo.queueFamilyIndexCount = buffer_info.queueFamilyIndexCount;
        createInfo.pQueueFamilyIndices = buffer_info.pQueueFamilyIndices;

        if (vkCreateBuffer(device.device, &createInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vulkan buffer!");
        }
    }

    VkMemoryRequirements VulkanBuffer::get_memory_requirements(VulkanDevice& device) {
        VkMemoryRequirements requirements;
        vkGetBufferMemoryRequirements(device.device, backend, &requirements);
        return requirements;
    }

    void VulkanBuffer::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
            
        vkDestroyBuffer(device.device, backend, nullptr);

        mark_destroyed();
    }
}
