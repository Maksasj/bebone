#include "vulkan_device_memory.h"

#include "vulkan_device.h"

#include "vulkan_buffer.h"
#include "vulkan_image.h"

namespace bebone::gfx::vulkan {
    VulkanDeviceMemory::VulkanDeviceMemory(VulkanDevice& device, VkMemoryRequirements memRequirements, VkMemoryPropertyFlags properties) {
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

    void VulkanDeviceMemory::bind_buffer_memory(VulkanDevice& device, std::shared_ptr<VulkanBuffer>& buffer) {
        bind_buffer_memory(device, *buffer);
    }

    void VulkanDeviceMemory::bind_image_memory(VulkanDevice& device, VulkanImage& image) {
        vkBindImageMemory(device.device(), image.backend, backend, 0);
    }

    void VulkanDeviceMemory::bind_image_memory(VulkanDevice& device, std::shared_ptr<VulkanImage>& image) {
        bind_image_memory(device, *image);
    }

    void VulkanDeviceMemory::map(VulkanDevice& device, const size_t& size, void** data) {
        vkMapMemory(device.device(), backend, 0, size, 0, data);
    }

    void VulkanDeviceMemory::unmap(VulkanDevice& device) {
        vkUnmapMemory(device.device(), backend);
    }

    void VulkanDeviceMemory::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
        
        vkFreeMemory(device.device(), backend, nullptr);

        mark_destroyed();
    }

    void VulkanDeviceMemory::upload_data(VulkanDevice& device, const void* src, const size_t& size) {
        void* data;

        map(device, size, &data);
        memcpy(data, src, size);
        unmap(device);
    }

    void VulkanDeviceMemory::upload_data(std::shared_ptr<VulkanDevice>& device, const void* src, const size_t& size) {
        upload_data(*device, src, size);
    }
}
