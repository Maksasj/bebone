#ifndef BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT
#define BEBONE_VULKAN_DESCRIPTOR_SET_LAYOUT

#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanDevice;
    class VulkanDescriptorSetLayoutBinding;

    class VulkanDescriptorSetLayout : public VulkanWrapper<VkDescriptorSetLayout>, private core::NonCopyable {
        public:
            VulkanDescriptorSetLayout(
                VulkanDevice& device,
                const std::vector<VulkanDescriptorSetLayoutBinding>& bindings);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
