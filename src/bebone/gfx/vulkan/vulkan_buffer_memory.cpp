#include "vulkan_buffer_memory.h"

namespace bebone::gfx {
    VulkanBufferMemory::VulkanBufferMemory(
        VulkanDevice& device,
        const size_t& size,
        VulkanBufferInfo buffer_info
    ) {
        buffer = std::make_unique<VulkanBuffer>(device, size, buffer_info);
        auto requirements = buffer->get_memory_requirements();

        memory = std::make_unique<VulkanDeviceMemory>(device, requirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        memory->bind_buffer_memory(buffer);
    }

    VulkanBufferMemory::~VulkanBufferMemory() {

    }

    void VulkanBufferMemory::upload_data(const void* src, const size_t& size) {
        memory->upload_data(src, size);
    }

    VkBuffer VulkanBufferMemory::get_vk_buffer() const {
        return buffer->get_vk_buffer();
    }

    size_t VulkanBufferMemory::get_size() const {
        return buffer->get_size();
    }

    void VulkanBufferMemory::copy_to_image(IVulkanImage& image) {
        return buffer->copy_to_image(image);
    }

    VkDeviceMemory VulkanBufferMemory::get_vk_device_memory() const {
        return memory->get_vk_device_memory();
    }
}
