#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H_

#include "../gfx_backend.h"
#include "vulkan_wrapper.tpp"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    enum VulkanDescriptorSetLayoutBindingType {
        BindlessUniform,
        BindlessSampler
    };

    class VulkanDescriptorSetLayoutBinding : public VulkanWrapper<VkDescriptorSetLayoutBinding> {
        public:
            VulkanDescriptorSetLayoutBinding(const VulkanDescriptorSetLayoutBindingType& type, const u32& binding);

            void destroy(VulkanDevice&) override;
    };
}

#endif
