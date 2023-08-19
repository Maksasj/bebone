#ifndef _BEBONE_GFX_VULKAN_VERTEX_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_VERTEX_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../../common/common.h"
#include "vulkan_buffer_impl.h"
#include "../device_impl.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::common;

    class VulkanVertexBufferImpl : public VulkanBufferImpl {
        private:
            uint32_t vertexCount;

        public:
            VulkanVertexBufferImpl(const std::vector<Vertex> &vertices, DeviceImpl& device) 
                : VulkanBufferImpl(
                    sizeof(Vertex) * vertices.size(), 
                    VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, 
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ) {
                
                vertexCount = static_cast<uint32_t>(vertices.size());
                VkDeviceSize bufferSize = sizeof(Vertex) * vertexCount;

                void* data;
                vkMapMemory(device.device(), get_buffer_memory(), 0, bufferSize, 0, &data);
                memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
                vkUnmapMemory(device.device(), get_buffer_memory());
            }

            ~VulkanVertexBufferImpl() {
                vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
