#include "vulkan_device_memory.h"

#include "vulkan_device.h"

#include "vulkan_buffer.h"
#include "vulkan_image.h"

namespace bebone::gfx {
    VulkanDeviceMemory::VulkanDeviceMemory(
        VulkanDevice& device,
        VkMemoryRequirements requirements,
        VkMemoryPropertyFlags properties
    ) : device_owner(device) {
        VkMemoryAllocateInfo alloc_info{};

        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = requirements.size;
        alloc_info.memoryTypeIndex = device.find_memory_type(requirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device.device, &alloc_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to allocate vulkan buffer memory");
            throw std::runtime_error("failed to allocate vulkan buffer memory!");
        }

        LOG_TRACE("Allocated Vulkan device memory");
    }

    VulkanDeviceMemory::~VulkanDeviceMemory() {
        vkFreeMemory(device_owner.device, backend, nullptr);

        LOG_TRACE("Freed Vulkan device memory");
    }

    void VulkanDeviceMemory::bind_buffer_memory(VulkanBuffer& buffer) {
        vkBindBufferMemory(device_owner.device, buffer.backend, backend, 0);
    }

    void VulkanDeviceMemory::bind_buffer_memory(std::shared_ptr<VulkanBuffer>& buffer) {
        bind_buffer_memory(*buffer);
    }

    void VulkanDeviceMemory::bind_image_memory(VulkanImage& image) {
        vkBindImageMemory(device_owner.device, image.backend, backend, 0);
    }

    void VulkanDeviceMemory::bind_image_memory(std::shared_ptr<VulkanImage>& image) {
        bind_image_memory(*image);
    }

    void VulkanDeviceMemory::map(const size_t& size, void** data) {
        vkMapMemory(device_owner.device, backend, 0, size, 0, data);
    }

    void VulkanDeviceMemory::unmap() {
        vkUnmapMemory(device_owner.device, backend);
    }

    void VulkanDeviceMemory::upload_data(const void* src, const size_t& size) {
        void* data;

        map(size, &data);
        memcpy(data, src, size);
        unmap();
    }

    /*
    void VulkanDeviceMemory::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkFreeMemory(device.device, backend, nullptr);

        LOG_TRACE("Freed Vulkan device memory");

        mark_destroyed();
    }
    */
}
