#include "vulkan_buffer_tuples.h"

namespace bebone::gfx::vulkan {
    VulkanBufferMemoryTuple::VulkanBufferMemoryTuple(
        const shared_ptr<VulkanBuffer>& buffer,
        const shared_ptr<VulkanDeviceMemory>& memory
    ) : buffer(buffer), memory(memory) {

    }

    void VulkanBufferMemoryTuple::destroy(VulkanDevice &device) {

    }
}
