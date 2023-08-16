#ifndef _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_UNIFORM_BUFFER_IMPLEMENTATION_H_

#include "../uniform_buffer_impl.h"
#include "vulkan_buffer_impl.h"

namespace bebone::gfx {
    using namespace bebone::common;

    class VulkanUniformBufferImpl : public VulkanBufferImpl , public UniformBufferImpl {
        private:
            void* _data;
            VkDescriptorSet* _descriptorSet;

        public:
            VulkanUniformBufferImpl(const size_t& size, DeviceImpl& device) 
                : VulkanBufferImpl(
                    size,
                    VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, 
                    VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, device
                ), _descriptorSet(nullptr) {

                vkMapMemory(device.device(), get_buffer_memory(), 0, size, 0, &_data);
            }

            void* data() override {
                return _data;
            }

            // Todo maybe in the future we will need to abstract descriptors and make this function virtual
            void bind_descriptor_set(VkDescriptorSet* descriptorSet) {
                _descriptorSet = descriptorSet;
            }

            VkDescriptorSet* get_descriptor_set() {
                return _descriptorSet;
            }

            ~VulkanUniformBufferImpl() {
                vkDestroyBuffer(get_device().device(), get_buffer(), nullptr);
                vkFreeMemory(get_device().device(), get_buffer_memory(), nullptr);
            }
    };
}

#endif
