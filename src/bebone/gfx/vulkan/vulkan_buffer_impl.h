#ifndef _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "vulkan_device.h"
#include "../../core/core.h"
#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    const static VkBufferUsageFlags VULKAN_BUFFER_ANY_USE_FLAG =
        VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT |
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT |
        VK_BUFFER_USAGE_TRANSFER_DST_BIT |
        VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT |
        VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT |
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT |
        VK_BUFFER_USAGE_STORAGE_BUFFER_BIT |
        VK_BUFFER_USAGE_INDEX_BUFFER_BIT |
        VK_BUFFER_USAGE_VERTEX_BUFFER_BIT |
        VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT |
        VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_BUFFER_BIT_EXT |
        VK_BUFFER_USAGE_TRANSFORM_FEEDBACK_COUNTER_BUFFER_BIT_EXT |
        VK_BUFFER_USAGE_CONDITIONAL_RENDERING_BIT_EXT |
        VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_BUILD_INPUT_READ_ONLY_BIT_KHR |
        VK_BUFFER_USAGE_ACCELERATION_STRUCTURE_STORAGE_BIT_KHR |
        VK_BUFFER_USAGE_SHADER_BINDING_TABLE_BIT_KHR;

    class VulkanBufferImpl : private core::NonCopyable {
        private:
            VulkanDevice& device;

            VkBuffer buffer;
            VkDeviceMemory bufferMemory;

            const size_t _size;

            void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage) {
                VkBufferCreateInfo bufferInfo{};
                bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
                bufferInfo.size = size;
                bufferInfo.usage = usage;
                bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

                if (vkCreateBuffer(device.device(), &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create vulkan buffer!");
                }
            }

            void allocate_memory(VkMemoryPropertyFlags properties) {
                VkMemoryRequirements memRequirements;
                vkGetBufferMemoryRequirements(device.device(), buffer, &memRequirements);

                VkMemoryAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
                allocInfo.allocationSize = memRequirements.size;
                allocInfo.memoryTypeIndex = device.findMemoryType(memRequirements.memoryTypeBits, properties);

                if (vkAllocateMemory(device.device(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate vulkan buffer memory!");
                }
            }

        public:
            VulkanBufferImpl(VkDeviceSize size, VkMemoryPropertyFlags properties, VulkanDevice& device) : device(device), _size(static_cast<size_t>(size)) {
                create_buffer(size, VULKAN_BUFFER_ANY_USE_FLAG);
                allocate_memory(properties);

                vkBindBufferMemory(device.device(), buffer, bufferMemory, 0);
            }

            ~VulkanBufferImpl() {
                vkDestroyBuffer(device.device(), buffer, nullptr);
                vkFreeMemory(device.device(), bufferMemory, nullptr);
            }

            VkBuffer get_buffer() const {
                return buffer;
            }

            size_t get_size() {
                return _size;
            }

            VkDeviceMemory get_buffer_memory() const {
                return bufferMemory;
            }
    };
}

#endif
