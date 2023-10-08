#ifndef _BEBONE_GFX_VULKAN_VERTEX_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_VERTEX_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "vulkan_buffer_impl.h"
#include "vulkan_device.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    template<class VertexType>
    class VulkanVertexBufferImpl : public VulkanBufferImpl {
        private:
            uint32_t vertexCount;

        public:
            VulkanVertexBufferImpl(const std::vector<VertexType> &vertices, VulkanDevice& device)
                : VulkanBufferImpl(
                    sizeof(VertexType) * vertices.size(),
                    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, // Todo actual this can be set to an any buffer type
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ) {
                
                vertexCount = static_cast<uint32_t>(vertices.size());
                VkDeviceSize bufferSize = sizeof(VertexType) * vertexCount;

                void* data;
                vkMapMemory(device.device(), get_buffer_memory(), 0, bufferSize, 0, &data);
                memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
                vkUnmapMemory(device.device(), get_buffer_memory());
            }

            ~VulkanVertexBufferImpl() {
                // vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                // vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
