#include "vulkan_device_memory.h"

#include "vulkan_device.h"

#include "vulkan_buffer.h"
#include "vulkan_image.h"

namespace bebone::gfx {
    VulkanDeviceMemory::VulkanDeviceMemory(
        VulkanDevice& device,
        VkMemoryRequirements requirements,
        VkMemoryPropertyFlags properties
    ) {
        VkMemoryAllocateInfo alloc_info{};

        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = requirements.size;
        alloc_info.memoryTypeIndex = device.find_memory_type(requirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device.device, &alloc_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to allocate vulkan buffer memory");
            throw std::runtime_error("failed to allocate vulkan buffer memory!");
        }
    }

    void VulkanDeviceMemory::bind_buffer_memory(VulkanDevice& device, VulkanBuffer& buffer) {
        vkBindBufferMemory(device.device, buffer.backend, backend, 0);
    }

    void VulkanDeviceMemory::bind_buffer_memory(VulkanDevice& device, std::shared_ptr<VulkanBuffer>& buffer) {
        bind_buffer_memory(device, *buffer);
    }

    void VulkanDeviceMemory::bind_image_memory(VulkanDevice& device, VulkanImage& image) {
        vkBindImageMemory(device.device, image.backend, backend, 0);
    }

    void VulkanDeviceMemory::bind_image_memory(VulkanDevice& device, std::shared_ptr<VulkanImage>& image) {
        bind_image_memory(device, *image);
    }

    void VulkanDeviceMemory::map(VulkanDevice& device, const size_t& size, void** data) {
        vkMapMemory(device.device, backend, 0, size, 0, data);
    }

    void VulkanDeviceMemory::unmap(VulkanDevice& device) {
        vkUnmapMemory(device.device, backend);
    }

    void VulkanDeviceMemory::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
        
        vkFreeMemory(device.device, backend, nullptr);

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
