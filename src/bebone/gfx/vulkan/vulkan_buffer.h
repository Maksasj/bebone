#ifndef _BEBONE_GFX_VULKAN_VULKAN_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_VULKAN_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_device_memory.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    class VulkanDevice;

    class VulkanBuffer;
    class VulkanDeviceMemory;

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

    struct VulkanBufferInfo {
        // VkStructureType sType;
        // const void* pNext;
        VkBufferCreateFlags flags = 0;
        // VkDeviceSize size;
        VkBufferUsageFlags usage = VULKAN_BUFFER_ANY_USE_FLAG;
        VkSharingMode sharingMode = VK_SHARING_MODE_EXCLUSIVE;
        uint32_t queueFamilyIndexCount = 0;
        uint32_t* pQueueFamilyIndices = nullptr;
    };

    using VulkanBufferMemoryTuple = std::tuple<std::shared_ptr<VulkanBuffer>, std::shared_ptr<VulkanDeviceMemory>>;

    class VulkanBuffer : public VulkanWrapper<VkBuffer>, private core::NonCopyable {
        public:
            VulkanBuffer(VulkanDevice& device, VkDeviceSize size, VulkanBufferInfo bufferInfo);

            VkMemoryRequirements get_memory_requirements(VulkanDevice& device);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
