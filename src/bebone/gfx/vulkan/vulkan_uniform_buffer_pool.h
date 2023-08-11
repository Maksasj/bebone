#ifndef _BEBONE_GFX_VULKAN_VULKAN_UNIFORM_BUFFER_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_UNIFORM_BUFFER_POOL_H_

#include <vector>

#include "../gfx_backend.h"
#include "../command_buffer_pool.h"

#include "../device_impl.h"

#include "vulkan_command_buffer.h"

#include "vulkan_uniform_buffer_impl.h"

namespace bebone::gfx {
    class VulkanUniformBufferPool {
        private:
            DeviceImpl& _device;

        public:
            std::vector<VulkanUniformBufferImpl*> uniformBuffers;

            VulkanUniformBufferImpl ubo0;
            VulkanUniformBufferImpl ubo1;

            VulkanUniformBufferPool(const size_t& size, const size_t& uniformBufferCount, DeviceImpl& device) : _device(device) , ubo0(size, device), ubo1(size, device) {
                // for(size_t i = 0; i < uniformBufferCount; ++i) {
                // uniformBuffers.push_back(VulkanUniformBufferImpl(size, device));
                // }

                (void) uniformBufferCount;

                uniformBuffers.resize(2);
                uniformBuffers[0] = &ubo0;
                uniformBuffers[1] = &ubo1;

               
               
               
                // uniformBuffers = std::vector<VulkanUniformBufferImpl>(2, size, device);
            }

            ~VulkanUniformBufferPool() {

            }
    };  
}

#endif
