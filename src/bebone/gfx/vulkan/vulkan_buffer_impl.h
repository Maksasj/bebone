#ifndef _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;

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

            void create_buffer(VkDeviceSize size, VkBufferUsageFlags usage);

            void allocate_memory(VkMemoryPropertyFlags properties);

        public:
            VulkanBufferImpl(VkDeviceSize size, VkMemoryPropertyFlags properties, VulkanDevice& device);

            ~VulkanBufferImpl();

            VkBuffer get_buffer() const;

            size_t get_size();

            VkDeviceMemory get_buffer_memory() const;
    };
}

#endif
