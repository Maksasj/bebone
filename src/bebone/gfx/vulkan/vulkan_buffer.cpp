#include "vulkan_buffer.h"

#include "vulkan_device.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanBuffer::VulkanBuffer(
        VulkanDevice& device,
        const size_t& size,
        VulkanBufferInfo bufferInfo
    )  : size(size) {
        VkBufferCreateInfo createInfo{};

        createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = bufferInfo.flags;
        createInfo.size = size;
        createInfo.usage = bufferInfo.usage;
        createInfo.sharingMode = bufferInfo.sharingMode;
        createInfo.queueFamilyIndexCount = bufferInfo.queueFamilyIndexCount;
        createInfo.pQueueFamilyIndices = bufferInfo.pQueueFamilyIndices;

        if (vkCreateBuffer(device.device(), &createInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vulkan buffer!");
        }
    }

    VkMemoryRequirements VulkanBuffer::get_memory_requirements(VulkanDevice& device) {
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device.device(), backend, &memRequirements);
        return memRequirements;
    }

    const size_t& VulkanBuffer::get_size() const {
        return size;
    }

    void VulkanBuffer::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
            
        vkDestroyBuffer(device.device(), backend, nullptr);

        mark_destroyed();
    }
}
