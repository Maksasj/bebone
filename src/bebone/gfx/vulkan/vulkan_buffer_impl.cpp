#include "vulkan_buffer_impl.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    void VulkanBufferImpl::create_buffer(VkDeviceSize size, VkBufferUsageFlags usage) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device.device(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vulkan buffer!");
        }
    }

    void VulkanBufferImpl::allocate_memory(VkMemoryPropertyFlags properties) {
        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device.device(), buffer, &memRequirements);

        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate vulkan buffer memory!");
        }
    }

    VulkanBufferImpl::VulkanBufferImpl(VkDeviceSize size, VkMemoryPropertyFlags properties, VulkanDevice& device) : device(device), _size(static_cast<size_t>(size)) {
        create_buffer(size, VULKAN_BUFFER_ANY_USE_FLAG);
        allocate_memory(properties);

        vkBindBufferMemory(device.device(), buffer, bufferMemory, 0);
    }

    VulkanBufferImpl::~VulkanBufferImpl() {
        vkDestroyBuffer(device.device(), buffer, nullptr);
        vkFreeMemory(device.device(), bufferMemory, nullptr);
    }

    VkBuffer VulkanBufferImpl::get_buffer() const {
        return buffer;
    }

    size_t VulkanBufferImpl::get_size() {
        return _size;
    }

    VkDeviceMemory VulkanBufferImpl::get_buffer_memory() const {
        return bufferMemory;
    }
}
