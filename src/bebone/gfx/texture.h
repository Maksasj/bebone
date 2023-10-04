#ifndef _BEBONE_GFX_TEXTURE_H_
#define _BEBONE_GFX_TEXTURE_H_

#include <vector>

#include "vulkan/vulkan_device.h"

#include "gfx_backend.h"

#include "vulkan/vulkan_command_buffer_pool.h"

namespace bebone::gfx {
    class Texture {
        public:
            VulkanDevice& _device;
            VulkanCommandBufferPool& _commandBufferPool;

            VkImage textureImage;
            VkDeviceMemory textureImageMemory;
            VkImageView textureImageView;
            VkSampler textureSampler;

            VkDescriptorSet* descriptorSet;

            Texture(VulkanDevice& device, VulkanCommandBufferPool& commandBufferPool) : _device(device), _commandBufferPool(commandBufferPool) {
                int texWidth = 512; 
                int texHeight = 512;
                int texChannels = 4;

                VkDeviceSize imageSize = texWidth * texHeight * texChannels;

                int* pixels = new int[512 * 512]();
                for(size_t i = 0; i < 512 * 512; ++i) {
                    pixels[i] = 0xff94f1;
                }

                VkBuffer stagingBuffer;
                VkDeviceMemory stagingBufferMemory;

                VkBufferCreateInfo bufferInfo{};
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.size = imageSize;
                bufferInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

                if (vkCreateBuffer(device.device(), &bufferInfo, nullptr, &stagingBuffer) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create vulkan buffer!");
                }
                
                {
                    VkMemoryRequirements memRequirements;
                    vkGetBufferMemoryRequirements(device.device(), stagingBuffer, &memRequirements);

                    VkMemoryAllocateInfo allocInfo{};
                    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                    allocInfo.allocationSize = memRequirements.size;
                    allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

                    if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &stagingBufferMemory) != VK_SUCCESS) {
                        throw std::runtime_error("failed to allocate vulkan buffer memory!");
                    }

                    vkBindBufferMemory(device.device(), stagingBuffer, stagingBufferMemory, 0);

                    void* data;
                    vkMapMemory(device.device(), stagingBufferMemory, 0, imageSize, 0, &data);
                        memcpy(data, pixels, static_cast<size_t>(imageSize));
                    vkUnmapMemory(device.device(), stagingBufferMemory);
                }


                VkImageCreateInfo imageInfo{};
                imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
                imageInfo.imageType = VK_IMAGE_TYPE_2D;
                imageInfo.extent.width = static_cast<uint32_t>(texWidth);
                imageInfo.extent.height = static_cast<uint32_t>(texHeight);
                imageInfo.extent.depth = 1;
                imageInfo.mipLevels = 1;
                imageInfo.arrayLayers = 1;
                imageInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
                imageInfo.tiling = VK_IMAGE_TILING_OPTIMAL;
                imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
                imageInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
                imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
                imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
                imageInfo.flags = 0; // Optional

                if (vkCreateImage(device.device(), &imageInfo, nullptr, &textureImage) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create image!");
                }


                VkMemoryRequirements memRequirements;
                vkGetImageMemoryRequirements(device.device(), textureImage, &memRequirements);

                VkMemoryAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocInfo.allocationSize = memRequirements.size;
                allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

                if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &textureImageMemory) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate image memory!");
                }

                vkBindImageMemory(device.device(), textureImage, textureImageMemory, 0);

                transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
                copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
                transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

                vkDestroyBuffer(device.device(), stagingBuffer, nullptr);
                vkFreeMemory(device.device(), stagingBufferMemory, nullptr);

                createImageViews();
                createSampler();
            }

            ~Texture() {
                // ...
                // ...
                //

                vkDestroySampler(_device.device(), textureSampler, nullptr);
                vkDestroyImageView(_device.device(), textureImageView, nullptr);
                vkDestroyImage(_device.device(), textureImage, nullptr);
                vkFreeMemory(_device.device(), textureImageMemory, nullptr);
            }

            void createImageViews() {
                VkImageViewCreateInfo viewInfo{};
                viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
                viewInfo.image = textureImage;
                viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
                viewInfo.format = VK_FORMAT_R8G8B8A8_SRGB;
                viewInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                viewInfo.subresourceRange.baseMipLevel = 0;
                viewInfo.subresourceRange.levelCount = 1;
                viewInfo.subresourceRange.baseArrayLayer = 0;
                viewInfo.subresourceRange.layerCount = 1;

                if (vkCreateImageView(_device.device(), &viewInfo, nullptr, &textureImageView) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create texture image view!");
                }
            }

            void createSampler() {
                VkSamplerCreateInfo samplerInfo{};
                samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
                samplerInfo.magFilter = VK_FILTER_LINEAR;
                samplerInfo.minFilter = VK_FILTER_LINEAR;

                samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
                samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

                samplerInfo.anisotropyEnable = VK_TRUE;
                samplerInfo.maxAnisotropy = _device.properties.limits.maxSamplerAnisotropy;
                samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
                samplerInfo.unnormalizedCoordinates = VK_FALSE;
                samplerInfo.compareEnable = VK_FALSE;
                samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

                samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
                samplerInfo.mipLodBias = 0.0f;
                samplerInfo.minLod = 0.0f;
                samplerInfo.maxLod = 0.0f;

                if (vkCreateSampler(_device.device(), &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create texture sampler!");
                }
            }

            void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
                VulkanCommandBufferPool& pool = static_cast<VulkanCommandBufferPool&>(_commandBufferPool);
                VkCommandBuffer commandBuffer = pool.begin_single_time_commands();

                VkBufferImageCopy region{};
                region.bufferOffset = 0;
                region.bufferRowLength = 0;
                region.bufferImageHeight = 0;

                region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                region.imageSubresource.mipLevel = 0;
                region.imageSubresource.baseArrayLayer = 0;
                region.imageSubresource.layerCount = 1;

                region.imageOffset = {0, 0, 0};
                region.imageExtent = {
                    width,
                    height,
                    1
                };

                vkCmdCopyBufferToImage(
                    commandBuffer,
                    buffer,
                    image,
                    VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
                    1,
                    &region
                );

                pool.end_single_time_commands(commandBuffer);
            }

            void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout) {
                VulkanCommandBufferPool& pool = static_cast<VulkanCommandBufferPool&>(_commandBufferPool);

                std::ignore = format;

                VkCommandBuffer commandBuffer = pool.begin_single_time_commands();

                VkImageMemoryBarrier barrier{};
                barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
                barrier.oldLayout = oldLayout;
                barrier.newLayout = newLayout;
                barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
                barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
                barrier.image = image;
                barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
                barrier.subresourceRange.baseMipLevel = 0;
                barrier.subresourceRange.levelCount = 1;
                barrier.subresourceRange.baseArrayLayer = 0;
                barrier.subresourceRange.layerCount = 1;

                barrier.srcAccessMask = 0; // TODO
                barrier.dstAccessMask = 0; // TODO

                VkPipelineStageFlags sourceStage;
                VkPipelineStageFlags destinationStage;

                if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
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
                    throw std::invalid_argument("unsupported layout transition!");
                }

                vkCmdPipelineBarrier(
                    commandBuffer,
                    sourceStage, destinationStage,
                    0,
                    0, nullptr,
                    0, nullptr,
                    1, &barrier
                );

                pool.end_single_time_commands(commandBuffer);
            }
    };
}

#endif
