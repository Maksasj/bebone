#include "vulkan_buffer.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer.h"

namespace bebone::gfx {
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

    void VulkanBuffer::copy_to_image(VulkanDevice& device, std::shared_ptr<VulkanImage>& image) {
        auto command_buffer = device.begin_single_time_commands();

        VkBufferImageCopy region{};
        region.bufferOffset = 0;
        region.bufferRowLength = 0;
        region.bufferImageHeight = 0;

        region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        region.imageSubresource.mipLevel = 0;
        region.imageSubresource.baseArrayLayer = 0;
        region.imageSubresource.layerCount = 1; // Todo

        region.imageOffset = { 0, 0, 0 };
        region.imageExtent = image->get_extent();

        vkCmdCopyBufferToImage(command_buffer->backend, backend, image->backend, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

        device.end_single_time_commands(command_buffer);
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
