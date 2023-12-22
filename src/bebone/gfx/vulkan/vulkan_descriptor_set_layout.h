#ifndef BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT
#define BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT

#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanDevice;

    class VulkanDescriptorSetLayout {
        private:

        public:
            VkDescriptorSetLayout descriptorSetLayout;

            VulkanDescriptorSetLayout(VulkanDevice& device, const std::vector<VkDescriptorSetLayoutBinding>& bindings);
    };
}

#endif
