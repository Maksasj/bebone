#include "vulkan_descriptor_set_layout_binding.h"

namespace bebone::gfx {
    using namespace bebone::core;

    VulkanDescriptorSetLayoutBinding::VulkanDescriptorSetLayoutBinding(const VulkanDescriptorSetLayoutBindingType& type, const u32& binding) {
        if(type == Uniform) {
            descriptor_set_layout_binding = {
                .binding = binding,
                .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                .descriptorCount = 65536,
                .stageFlags = VK_SHADER_STAGE_ALL,
                .pImmutableSamplers = nullptr
            };
        } else if(type == Storage) {
            descriptor_set_layout_binding = {
                .binding = binding,
                .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
                .descriptorCount = 65536,
                .stageFlags = VK_SHADER_STAGE_ALL,
                .pImmutableSamplers = nullptr
            };
        } else if(type == Sampler) {
            descriptor_set_layout_binding = {
                .binding = binding,
                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .descriptorCount = 65536,
                .stageFlags = VK_SHADER_STAGE_ALL,
                .pImmutableSamplers = nullptr
            };
        }
    }
}
