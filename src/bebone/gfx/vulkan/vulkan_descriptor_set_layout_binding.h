#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H_

#include "../gfx_backend.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    class VulkanDescriptorSetLayoutBinding {
        private:

        public:
            VkDescriptorSetLayoutBinding binding;

            static VulkanDescriptorSetLayoutBinding bindless_uniform(const u32& binding);
            static VulkanDescriptorSetLayoutBinding bindless_sampler2d(const u32& binding);
    };
}

#endif
