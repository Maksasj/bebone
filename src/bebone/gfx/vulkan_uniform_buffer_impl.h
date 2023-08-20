#ifndef _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_

#include "gpu_resource.h"

#include "vulkan/vulkan_buffer_impl.h"

namespace bebone::gfx {
    using namespace bebone::common;

    class VulkanUniformBufferImpl : public VulkanBufferImpl , public GPUResource {
        private:
            void* _data;

        public:
            VulkanUniformBufferImpl(const size_t& size, DeviceImpl& device, const GPUResourceHandle& handle) 
                : VulkanBufferImpl(
                    size,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ), GPUResource(handle) {

                vkMapMemory(device.device(), get_buffer_memory(), 0, size, 0, &_data);

                *static_cast<float*>(_data) = 0.2f;
            }

            void* data() {
                return _data;
            }

            ~VulkanUniformBufferImpl() {
                vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
