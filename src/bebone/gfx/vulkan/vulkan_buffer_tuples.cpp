#include "vulkan_buffer_tuples.h"

namespace bebone::gfx {
    VulkanBufferMemoryTuple::VulkanBufferMemoryTuple(
        const shared_ptr<VulkanBuffer>& buffer,
        const shared_ptr<VulkanDeviceMemory>& memory
    ) : buffer(buffer), memory(memory) {

    }

    void VulkanBufferMemoryTuple::upload_data(std::shared_ptr<VulkanDevice>& device, const void* src, const size_t& size) {
        memory->upload_data(device, src, size);
    }

    void VulkanBufferMemoryTuple::upload_data(VulkanDevice& device, const void* src, const size_t& size) {
        memory->upload_data(device, src, size);
    }
}
