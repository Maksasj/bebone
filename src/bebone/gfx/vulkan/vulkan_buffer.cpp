#include "vulkan_buffer.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    void VulkanBuffer::create_buffer(VulkanDevice& device, VkDeviceSize size, VkBufferUsageFlags usage) {
        VkBufferCreateInfo bufferInfo{};
        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        bufferInfo.size = size;
        bufferInfo.usage = usage;
        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        if (vkCreateBuffer(device.device(), &bufferInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create vulkan buffer!");
        }
    }

    VulkanBuffer::VulkanBuffer(VulkanDevice& device, VkDeviceSize size, VkMemoryPropertyFlags properties) {
        create_buffer(device, size, VULKAN_BUFFER_ANY_USE_FLAG);

        VkMemoryRequirements memRequirements;
        vkGetBufferMemoryRequirements(device.device(), backend, &memRequirements);

        bufferMemory = std::make_shared<VulkanDeviceMemory>(device, memRequirements, properties);
        bufferMemory->bind_buffer_memory(device, *this);
    }

    void VulkanBuffer::upload_data(std::shared_ptr<VulkanDevice>& device, const void* src, const size_t& size) {
        void* data;

        bufferMemory->map(device, size, &data);
        memcpy(data, src, size);
        bufferMemory->unmap(device);
    }

    VkBuffer VulkanBuffer::get_buffer() const {
        return backend;
    }

    void VulkanBuffer::destroy(bebone::gfx::VulkanDevice &device) {
        vkDestroyBuffer(device.device(), backend, nullptr);

        bufferMemory->destroy(device);
    }
}
