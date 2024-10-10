#ifndef _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_
#define _BEBONE_GFX_VULKAN_BUFFER_TUPLES_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_buffer.h"
#include "vulkan_device_memory.h"

namespace bebone::gfx {
    class VulkanDevice;

    using namespace bebone::core;

    struct VulkanBufferMemory : public IVulkanBuffer, public IVulkanDeviceMemory {
        private:
            std::unique_ptr<VulkanBuffer> buffer;
            std::unique_ptr<VulkanDeviceMemory> memory;

        public:
            VulkanBufferMemory(VulkanDevice& device, const size_t& size, VulkanBufferInfo buffer_info = {});

            template<typename T>
            VulkanBufferMemory(
                VulkanDevice& device,
                const std::vector<T>& data,
                VulkanBufferInfo buffer_info = {}
            ) {
                const auto size = sizeof(T) * data.size();

                buffer = std::make_unique<VulkanBuffer>(device, size, buffer_info);

                auto requirements = buffer->get_memory_requirements();

                memory = std::make_unique<VulkanDeviceMemory>(device, requirements, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT); // Todo this should be configurable
                memory->bind_buffer_memory(buffer);

                memory->upload_data(data.data(), size);
            }

            ~VulkanBufferMemory();

            void upload_data(const void* src, const size_t& size);

            VkBuffer get_vulkan_buffer() const override;
            void copy_to_image(IVulkanImage& image) override;
            size_t get_size() const override;

            VkDeviceMemory get_vulkan_device_memory() const;
    };
}

#endif
