#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include "gfx_backend.h"
#include "device.h"

#include "../common/common.h"

using namespace bebone::common;

class Model {
    public:
        Model(MyEngineDevice& device, const std::vector<Vertex> &vertices) : device(device) {
            createVertexBuffers(vertices);
        }

        ~Model() {
            vkDestroyBuffer(device.device(), vertexBuffer, nullptr);
            vkFreeMemory(device.device(), vertexBufferMemory, nullptr);
        }

        Model(const Model &) = delete;
        void operator=(const Model &) = delete;
        Model(Model &&) = delete;
        Model &operator=(Model &&) = delete;

        static std::vector<VkVertexInputBindingDescription> getBindingDescriptions() {
            std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);
            
            bindingDescriptions[0].binding = 0;
            bindingDescriptions[0].stride = sizeof(Vertex);
            bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescriptions;
        }
        
        static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
            std::vector<VkVertexInputAttributeDescription> atrributeDescriptions(2);
            
            atrributeDescriptions[0].binding = 0;
            atrributeDescriptions[0].location = 0;
            atrributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
            atrributeDescriptions[0].offset = offsetof(Vertex, x);

            atrributeDescriptions[1].binding = 0;
            atrributeDescriptions[1].location = 1;
            atrributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            atrributeDescriptions[1].offset = offsetof(Vertex, r);

            return atrributeDescriptions;
        }


        MyEngineDevice& device;

        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        uint32_t vertexCount;

    private:
        void createVertexBuffers(const std::vector<Vertex> &vertices) {
            vertexCount = static_cast<uint32_t>(vertices.size());
            VkDeviceSize bufferSize = sizeof(Vertex) * vertexCount;

            device.createBuffer(bufferSize, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, vertexBuffer, vertexBufferMemory);

            void* data;
            vkMapMemory(device.device(), vertexBufferMemory, 0, bufferSize, 0, &data);
            memcpy(data, vertices.data(), static_cast<size_t>(bufferSize));
            vkUnmapMemory(device.device(), vertexBufferMemory);
        }
};

#endif
