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
    class VulkanImage;

    class VulkanDeviceMemory : public VulkanWrapper<VkDeviceMemory>, private core::NonCopyable {
        public:
            VulkanDeviceMemory(VulkanDevice& device, VkMemoryRequirements memRequirements, VkMemoryPropertyFlags properties);

            void bind_buffer_memory(
                VulkanDevice& device,
                VulkanBuffer& buffer);

            void bind_buffer_memory(
                VulkanDevice& device,
                std::shared_ptr<VulkanBuffer>& buffer);

            void bind_image_memory(
                VulkanDevice& device,
                VulkanImage& image);

            void bind_image_memory(
                VulkanDevice& device,
                std::shared_ptr<VulkanImage>& image);

            void map(std::shared_ptr<VulkanDevice>& device, const size_t& size, void** data);
            void unmap(std::shared_ptr<VulkanDevice>& device);

            void upload_data(
                std::shared_ptr<VulkanDevice>& device,
                const void* src,
                const size_t& size);

            void destroy(VulkanDevice &device) override;
    };
}

#endif
