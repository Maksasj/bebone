#ifndef BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT
#define BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT

#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanDescriptorSetLayout {
        private:

        public:
            VulkanDescriptorSetLayout(VulkanDescriptorPool& descriptorPool) {
                // descriptorPool.create_descriptor_set_layout(bindings);
            }
    };
}

#endif
