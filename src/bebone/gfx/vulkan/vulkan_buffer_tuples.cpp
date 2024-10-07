#include "vulkan_buffer_tuples.h"

namespace bebone::gfx {
    VulkanBufferMemoryTuple::VulkanBufferMemoryTuple(
        VulkanDevice& device,
        const size_t& size,
        VulkanBufferInfo buffer_info
    ) {
        buffer = std::make_unique<VulkanBuffer>(device, size, buffer_info);
        auto requirements = buffer->get_memory_requirements();

        memory = std::make_unique<VulkanDeviceMemory>(device, requirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
        memory->bind_buffer_memory(buffer);
    }

    void VulkanBufferMemoryTuple::upload_data(const void* src, const size_t& size) {
        memory->upload_data(src, size);
    }
}
