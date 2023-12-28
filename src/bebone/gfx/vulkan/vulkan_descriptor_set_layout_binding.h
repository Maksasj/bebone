#ifndef BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H
#define BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT_BINDING_H

#include "../gfx_backend.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDescriptorSetLayoutBinding {
        private:

        public:
            VkDescriptorSetLayoutBinding binding;

            static VulkanDescriptorSetLayoutBinding bindless_uniform(const u32& binding);
    };
}

#endif
