#include "vulkan_image.h"

#include "vulkan_device.h"
#include "vulkan_image_view.h"
#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanImage::VulkanImage(const VkImage& image) {
        backend = image;
    }

    VulkanImage::VulkanImage(
        VulkanDevice& device,
        VkFormat format,
        VkExtent3D extent,
        VulkanImageInfo image_info
    ) {
        VkImageCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        create_info.pNext = nullptr;
        create_info.flags = image_info.flags;
        create_info.imageType = image_info.imageType;
        create_info.format = format;
        create_info.extent = extent;
        create_info.mipLevels = image_info.mipLevels;
        create_info.arrayLayers = image_info.arrayLayers;
        create_info.samples = image_info.samples;
        create_info.tiling = image_info.tiling;
        create_info.usage = image_info.usage;
        create_info.sharingMode = image_info.sharingMode;
        create_info.queueFamilyIndexCount = image_info.queueFamilyIndexCount;
        create_info.pQueueFamilyIndices = image_info.pQueueFamilyIndices;
        create_info.initialLayout = image_info.initialLayout;

        if(vkCreateImage(device.device, &create_info, nullptr, &backend) != VK_SUCCESS)
            throw std::runtime_error("failed to create image!");
    }

    // Todo clear out this
    void VulkanImage::transition_layout(
        VulkanCommandBufferPool& pool,
        VulkanDevice& device,
        VkImageLayout old_layout,
        VkImageLayout new_layout
    ) {
        VkCommandBuffer command_buffer = pool.begin_single_time_commands(device);

        VkImageMemoryBarrier barrier{};

        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = old_layout;
        barrier.newLayout = new_layout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = backend;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags source_stage;
        VkPipelineStageFlags destination_stage;

        if(old_layout == VK_IMAGE_LAYOUT_UNDEFINED && new_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            source_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destination_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } else if (old_layout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && new_layout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            source_stage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destination_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        } else
            throw std::runtime_error("unsupported layout transition!");

        vkCmdPipelineBarrier(command_buffer, source_stage, destination_stage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        pool.end_single_time_commands(device, command_buffer);
    }

    VkMemoryRequirements VulkanImage::get_memory_requirements(VulkanDevice& device) {
        VkMemoryRequirements requirements;

        vkGetImageMemoryRequirements(device.device, backend, &requirements);

        return requirements;
    }

    void VulkanImage::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyImage(device.device, backend, nullptr);

        mark_destroyed();
    }
}
