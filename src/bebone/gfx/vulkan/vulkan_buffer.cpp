#include "vulkan_buffer.h"

#include "vulkan_device.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanBuffer::VulkanBuffer(
        VulkanDevice& device,
        const size_t& size,
        VulkanBufferInfo buffer_info
    )  : size(size) {
        VkBufferCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        create_info.pNext = nullptr;
        create_info.flags = buffer_info.flags;
        create_info.size = size;
        create_info.usage = buffer_info.usage;
        create_info.sharingMode = buffer_info.sharing_mode;
        create_info.queueFamilyIndexCount = buffer_info.queue_family_index_count;
        create_info.pQueueFamilyIndices = buffer_info.ptr_queue_family_indices;

        if(vkCreateBuffer(device.device, &create_info, nullptr, &backend) != VK_SUCCESS)
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
