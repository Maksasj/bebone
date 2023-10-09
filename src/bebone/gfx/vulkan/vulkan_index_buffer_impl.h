#ifndef _BEBONE_GFX_VULKAN_INDEX_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_INDEX_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "vulkan_buffer_impl.h"
#include "vulkan_device.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanIndexBufferImpl : public VulkanBufferImpl {
        public:
            VulkanIndexBufferImpl(const std::vector<int> &indices, VulkanDevice& device) 
                : VulkanBufferImpl(
                    sizeof(int) * indices.size(), 
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ) {

                void* data;
                vkMapMemory(device.device(), get_buffer_memory(), 0, get_size(), 0, &data);
                memcpy(data, indices.data(), get_size());
                vkUnmapMemory(device.device(), get_buffer_memory());
            }

            ~VulkanIndexBufferImpl() {
                // vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                // vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
