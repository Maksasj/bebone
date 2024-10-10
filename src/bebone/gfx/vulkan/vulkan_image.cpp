#include "vulkan_image.h"

#include "vulkan_device.h"
#include "vulkan_command_buffer_pool.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanImage::VulkanImage(VulkanDevice& device, const VkImage& arg) : device_owner(device), swap_chain(true) {
        this->image = arg;
    }

    VulkanImage::VulkanImage(
        VulkanDevice& device,
        VkFormat format,
        VkExtent3D extent,
        VulkanImageInfo image_info
    ) : device_owner(device), swap_chain(false), extent(extent) {
        VkImageCreateInfo create_info{};

        create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        create_info.pNext = nullptr;
        create_info.flags = image_info.flags;
        create_info.imageType = image_info.image_type;
        create_info.format = format;
        create_info.extent = extent;
        create_info.mipLevels = image_info.mip_levels;
        create_info.arrayLayers = image_info.array_layers;
        create_info.samples = image_info.samples;
        create_info.tiling = image_info.tiling;
        create_info.usage = image_info.usage;
        create_info.sharingMode = image_info.sharing_mode;
        create_info.queueFamilyIndexCount = image_info.queue_family_index_count;
        create_info.pQueueFamilyIndices = image_info.ptr_queue_family_indices;
        create_info.initialLayout = image_info.initial_layout;

        if(vkCreateImage(device.device, &create_info, nullptr, &image) != VK_SUCCESS) {
            LOG_ERROR("Failed to create image");
            throw std::runtime_error("failed to create image!");
        }

        LOG_TRACE("Created Vulkan image");
    }

    VulkanImage::~VulkanImage() {
        if(!swap_chain)
            vkDestroyImage(device_owner.device, image, nullptr);

        LOG_DEBUG("Destroyed Vulkan image");
    };

    // Todo, clear out this
    void VulkanImage::transition_layout(
        VkImageLayout old_layout,
        VkImageLayout new_layout
    ) {
        auto command_buffer = device_owner.begin_single_time_commands();

        VkImageMemoryBarrier barrier{};

        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
        barrier.oldLayout = old_layout;
        barrier.newLayout = new_layout;
        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
        barrier.image = image;
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
        } else {
            LOG_ERROR("Unsupported image layout transition");
            throw std::runtime_error("unsupported layout transition!");
        }

        vkCmdPipelineBarrier(command_buffer->backend, source_stage, destination_stage, 0, 0, nullptr, 0, nullptr, 1, &barrier);

        device_owner.end_single_time_commands(command_buffer);
    }

    VkExtent3D VulkanImage::get_extent() const {
        return extent;
    }

    VkMemoryRequirements VulkanImage::get_memory_requirements() {
        VkMemoryRequirements requirements;

        vkGetImageMemoryRequirements(device_owner.device, image, &requirements);

        return requirements;
    }

    VkImage VulkanImage::get_vulkan_image() const {
        return image;
    }
}
