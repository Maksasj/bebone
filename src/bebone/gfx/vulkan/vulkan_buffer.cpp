#include "vulkan_buffer.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    void VulkanBuffer::create_buffer(VkDeviceSize size, VkBufferUsageFlags usage) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device.device(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vulkan buffer!");
        }
    }

    void VulkanBuffer::allocate_memory(VkMemoryPropertyFlags properties) {
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device.device(), buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = device.find_memory_type(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate vulkan buffer memory!");
        }
    }

    VulkanBuffer::VulkanBuffer(VkDeviceSize size, VkMemoryPropertyFlags properties, VulkanDevice& device) : device(device), _size(static_cast<size_t>(size)) {
        create_buffer(size, VULKAN_BUFFER_ANY_USE_FLAG);
        allocate_memory(properties);

        vkBindBufferMemory(device.device(), buffer, bufferMemory, 0);
    }

    VulkanBuffer::~VulkanBuffer() {
        vkDestroyBuffer(device.device(), buffer, nullptr);
        vkFreeMemory(device.device(), bufferMemory, nullptr);
    }

    void VulkanBuffer::upload_data(const void* src, const size_t& size) {
        void* data;
        vkMapMemory(device.device(), bufferMemory, 0, size, 0, &data);
        memcpy(data, src, size);
        vkUnmapMemory(device.device(), bufferMemory);
    }

    VkBuffer VulkanBuffer::get_buffer() const {
        return buffer;
    }

    size_t VulkanBuffer::get_size() {
        return _size;
    }

    VkDeviceMemory VulkanBuffer::get_buffer_memory() const {
        return bufferMemory;
    }
}
