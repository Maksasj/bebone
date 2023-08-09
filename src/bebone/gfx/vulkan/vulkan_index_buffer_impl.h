#ifndef _BEBONE_GFX_VULKAN_INDEX_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_INDEX_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../../common/common.h"
#include "../buffer_impl.h"
#include "../device_impl.h"

#include "../gfx_backend.h"

#include "vulkan_buffer_impl.h"

namespace bebone::gfx {
    using namespace bebone::common;

    class VulkanIndexBufferImpl : public VulkanBufferImpl {
        private:
            uint32_t vertexCount;

        public:
            VulkanIndexBufferImpl(const std::vector<int> &indices, DeviceImpl& device) 
                : VulkanBufferImpl(
                    sizeof(int) * indices.size(), 
                    VK_BUFFER_USAGE_INDEX_BUFFER_BIT, 
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ) {
                
                vertexCount = static_cast<uint32_t>(indices.size());
                VkDeviceSize bufferSize = sizeof(int) * vertexCount;

                void* data;
                vkMapMemory(device.device(), get_buffer_memory(), 0, bufferSize, 0, &data);
                memcpy(data, indices.data(), static_cast<size_t>(bufferSize));
                vkUnmapMemory(device.device(), get_buffer_memory());
            }

            ~VulkanIndexBufferImpl() {
                vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
