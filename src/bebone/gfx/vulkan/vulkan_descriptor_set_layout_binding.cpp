#include "vulkan_descriptor_set_layout_binding.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanDescriptorSetLayoutBinding VulkanDescriptorSetLayoutBinding::bindless_uniform(const u32& binding) {
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
}
