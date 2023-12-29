#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_SET_LAYOUT_H_

#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx::vulkan {
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
