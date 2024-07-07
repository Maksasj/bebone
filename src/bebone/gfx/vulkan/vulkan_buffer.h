#ifndef _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_device_memory.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;

    class VulkanBuffer;
    class VulkanDeviceMemory;

    const static VkBufferUsageFlags vulkan_buffer_any_use_flag =
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
        // VkStructureType type;
        // const void* ptr_next;
        VkBufferCreateFlags flags = 0;
        // VkDeviceSize size;
        VkBufferUsageFlags usage = vulkan_buffer_any_use_flag;
        VkSharingMode sharing_mode = VK_SHARING_MODE_EXCLUSIVE;
        uint32_t queue_family_index_count = 0;
        uint32_t* ptr_queue_family_indices = nullptr;
    };

    class VulkanBuffer : public VulkanWrapper<VkBuffer>, private core::NonCopyable {
        private:
            size_t size; // Todo, Do we really need to store buffer size there ?

        public:
            VulkanBuffer(VulkanDevice& device, const size_t& size, VulkanBufferInfo buffer_info);

            VkMemoryRequirements get_memory_requirements(VulkanDevice& device);

            void copy_to_image(VulkanDevice& device, std::shared_ptr<VulkanImage>& image);

            const size_t& get_size() const;

            void destroy(VulkanDevice& device) override;
    };
}

#endif
