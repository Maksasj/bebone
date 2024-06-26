#include "vulkan_buffer.h"

#include "vulkan_device.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanBuffer::VulkanBuffer(
        VulkanDevice& device,
        const size_t& size,
        VulkanBufferInfo buffer_info
    )  : size(size) {
        VkBufferCreateInfo create_Info{};

        create_Info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        create_Info.pNext = nullptr;
        create_Info.flags = buffer_info.flags;
        create_Info.size = size;
        create_Info.usage = buffer_info.usage;
        create_Info.sharingMode = buffer_info.sharing_mode;
        create_Info.queueFamilyIndexCount = buffer_info.queue_family_index_count;
        create_Info.pQueueFamilyIndices = buffer_info.ptr_queue_family_indices;

        if(vkCreateBuffer(device.device, &create_Info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("failed to create vulkan buffer!");
    }

    VkMemoryRequirements VulkanBuffer::get_memory_requirements(VulkanDevice& device) {
        VkMemoryRequirements requirements;

        vkGetBufferMemoryRequirements(device.device, backend, &requirements);

        return requirements;
    }

    const size_t& VulkanBuffer::get_size() const {
        return size;
    }

    void VulkanBuffer::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;
            
        vkDestroyBuffer(device.device, backend, nullptr);

        mark_destroyed();
    }
}
