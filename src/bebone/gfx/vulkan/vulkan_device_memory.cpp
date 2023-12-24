#include "vulkan_device_memory.h"

#include "vulkan_device.h"
#include "vulkan_buffer.h"

namespace bebone::gfx {
    VulkanDeviceMemory::VulkanDeviceMemory(VkMemoryRequirements memRequirements, VkMemoryPropertyFlags properties, VulkanDevice& device) {
        VkMemoryAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = device.find_memory_type(memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate vulkan buffer memory!");
        }
    }

    void VulkanDeviceMemory::bind_buffer_memory(VulkanDevice& device, VulkanBuffer& buffer) {
        vkBindBufferMemory(device.device(), buffer.backend, backend, 0);
    }

    void VulkanDeviceMemory::map(std::shared_ptr<VulkanDevice>& device, const size_t& size, void** data) {
        vkMapMemory(device->device(), backend, 0, size, 0, data);
    }

    void VulkanDeviceMemory::unmap(std::shared_ptr<VulkanDevice>& device) {
        vkUnmapMemory(device->device(), backend);
    }

    void VulkanDeviceMemory::destroy(VulkanDevice &device) {
        vkFreeMemory(device.device(), backend, nullptr);
    }
}
