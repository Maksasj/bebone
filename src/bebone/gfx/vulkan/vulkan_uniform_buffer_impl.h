#ifndef _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_

#include <vector>

#include "../../common/common.h"
#include "../buffer_impl.h"
#include "../device_impl.h"

#include "../gfx_backend.h"

#include "vulkan_buffer_impl.h"

namespace bebone::gfx {
    using namespace bebone::common;

    class VulkanUniformBufferImpl : public VulkanBufferImpl {
        private:
            void* data;

        public:
            VulkanUniformBufferImpl(const size_t& size, DeviceImpl& device) 
                : VulkanBufferImpl(
                    size,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ) {

                vkMapMemory(device.device(), get_buffer_memory(), 0, size, 0, &data);

                float x = 0.5;
                memcpy(data, &x, sizeof(float));
            }

            ~VulkanUniformBufferImpl() {
                vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
