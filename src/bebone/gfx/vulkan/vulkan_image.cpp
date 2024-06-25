#include "vulkan_image.h"

#include "vulkan_device.h"
#include "vulkan_image_view.h"
#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    VulkanImage::VulkanImage(const VkImage& image) {
        backend = image;
    }

    VulkanImage::VulkanImage(VulkanDevice& device, VkFormat format, VkExtent3D extent, VulkanImageInfo imageInfo) {
        VkImageCreateInfo createInfo{};

        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        createInfo.pNext = nullptr;
        createInfo.flags = imageInfo.flags;
        createInfo.imageType = imageInfo.imageType;
        createInfo.format = format;
        createInfo.extent = extent;
        createInfo.mipLevels = imageInfo.mipLevels;
        createInfo.arrayLayers = imageInfo.arrayLayers;
        createInfo.samples = imageInfo.samples;
        createInfo.tiling = imageInfo.tiling;
        createInfo.usage = imageInfo.usage;
        createInfo.sharingMode = imageInfo.sharingMode;
        createInfo.queueFamilyIndexCount = imageInfo.queueFamilyIndexCount;
        createInfo.pQueueFamilyIndices = imageInfo.pQueueFamilyIndices;
        createInfo.initialLayout = imageInfo.initialLayout;

        if (vkCreateImage(device.device(), &createInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }
    }

    // Todo clear out this
    void VulkanImage::transition_layout(VulkanCommandBufferPool& pool, VulkanDevice& device, VkImageLayout oldLayout, VkImageLayout newLayout) {
        VkCommandBuffer commandBuffer = pool.begin_single_time_commands(device);

        VkImageMemoryBarrier barrier{};
        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = oldLayout;
        barrier.newLayout = newLayout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = backend;
        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
        barrier.subresourceRange.baseMipLevel = 0;
        barrier.subresourceRange.levelCount = 1;
        barrier.subresourceRange.baseArrayLayer = 0;
        barrier.subresourceRange.layerCount = 1;

        VkPipelineStageFlags sourceStage;
        VkPipelineStageFlags destinationStage;

        if(oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
            barrier.srcAccessMask = 0;
            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;

            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
        } else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;

            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
        } else {
            throw std::runtime_error("unsupported layout transition!");
        }

        vkCmdPipelineBarrier(commandBuffer, sourceStage, destinationStage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        pool.end_single_time_commands(device, commandBuffer);
    }

    VkMemoryRequirements VulkanImage::get_memory_requirements(VulkanDevice& device) {
        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device.device(), backend, &memRequirements);
        return memRequirements;
    }

    void VulkanImage::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyImage(device.device(), backend, nullptr);

        mark_destroyed();
    }
}
