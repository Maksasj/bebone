#ifndef _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_

#include "../gpu_resource.h"

#include "vulkan_buffer_impl.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanUniformBufferImpl : public VulkanBufferImpl , public GPUResource<UniformBufferHandle> {
        private:
            void* _data;

        public:
            VulkanUniformBufferImpl(const size_t& size, VulkanDevice& device, const size_t& handleIndex) 
                : VulkanBufferImpl(
                    size,
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ), GPUResource<UniformBufferHandle>(UniformBufferHandle(handleIndex)) {

                vkMapMemory(device.device(), get_buffer_memory(), 0, size, 0, &_data);
            }

            template<class T>
            void set_data(const T& data) {
                *static_cast<T*>(_data) = data;
            }

            ~VulkanUniformBufferImpl() {
                // vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                // vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
