#ifndef _BEBONE_GFX_VULKAN_VERTEX_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_VERTEX_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../../common/common.h"
#include "../vertex_buffer_impl.h"
#include "../device.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::common;

    class VulkanVertexBufferImpl : public VertexBufferImpl {
        private:
            MyEngineDevice& _device;
            VkBuffer vertexBuffer;
            VkDeviceMemory vertexBufferMemory;
            uint32_t vertexCount;

        public:
            VulkanVertexBufferImpl(const std::vector<Vertex> &vertices, MyEngineDevice& device) : _device(device) {
                vertexCount = static_cast<uint32_t>(vertices.size());
                VkDeviceSize bufferSize = sizeof(Vertex) * vertexCount;

                device.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);

                void* data;
                vkMapMemory(device.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
                memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
                vkUnmapMemory(device.device(), vertexBufferMemory);
            }

            ~VulkanVertexBufferImpl() {
                vkDestroyBuffer(_device.device(), vertexBuffer, nullptr);
                vkFreeMemory(_device.device(), vertexBufferMemory, nullptr);
            }

            VkBuffer get_buffer() {
                return vertexBuffer;
            }
    };
}

#endif
