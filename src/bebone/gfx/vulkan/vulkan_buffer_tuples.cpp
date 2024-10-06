#include "vulkan_buffer_tuples.h"

namespace bebone::gfx {
    VulkanBufferMemoryTuple::VulkanBufferMemoryTuple(
        unique_ptr<VulkanBuffer>& buffer,
        unique_ptr<VulkanDeviceMemory>& memory
    ) : buffer(std::move(buffer)), memory(std::move(memory)) {

    }

    void VulkanBufferMemoryTuple::upload_data(const void* src, const size_t& size) {
        memory->upload_data(src, size);
    }
}
