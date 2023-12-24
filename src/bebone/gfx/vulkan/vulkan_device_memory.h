#ifndef _BEBONE_GFX_VULKAN_BUFFER_DEVICE_MEMORY_H_
#define _BEBONE_GFX_VULKAN_BUFFER_DEVICE_MEMORY_H_

#include <vector>

#include "../../core/core.h"
#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanBuffer;

    class VulkanDeviceMemory : public VulkanWrapper<VkDeviceMemory>, private core::NonCopyable {
        public:
            VulkanDeviceMemory(VkMemoryRequirements memRequirements, VkMemoryPropertyFlags properties, VulkanDevice& device);

            void bind_buffer_memory(VulkanDevice& device, VulkanBuffer& buffer);

            void map(std::shared_ptr<VulkanDevice>& device, const size_t& size, void** data);
            void unmap(std::shared_ptr<VulkanDevice>& device);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
