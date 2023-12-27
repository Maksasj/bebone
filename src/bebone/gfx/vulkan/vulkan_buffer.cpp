#include "vulkan_buffer.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanBuffer::VulkanBuffer(VulkanDevice& device, VkDeviceSize size, VulkanBufferInfo bufferInfo) {//VkMemoryPropertyFlags properties) {
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

    void VulkanBuffer::destroy(bebone::gfx::VulkanDevice &device) {
        vkDestroyBuffer(device.device(), backend, nullptr);
    }
}
