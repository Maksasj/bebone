#ifndef BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H
#define BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H

#include "../gfx_backend.h"

namespace bebone::gfx {
    class VulkanDescriptorSetLayoutBinding {
        private:

        public:
            VkDescriptorSetLayoutBinding binding;

            static VulkanDescriptorSetLayoutBinding bindless_uniform(const u32& binding) {
                return {
                    .binding = {
                        .binding = binding,
                        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                        .descriptorCount = 65536,
                        .stageFlags = VK_SHADER_STAGE_ALL,
                        .pImmutableSamplers = nullptr
                    }
                };
            }
    };
}

#endif
