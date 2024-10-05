#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_LAYOUT_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_LAYOUT_H_

#include "../gfx_backend.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanDevice;
    class VulkanDescriptorSetLayoutBinding;

    class VulkanDescriptorSetLayout : public VulkanWrapper<VkDescriptorSetLayout>, private core::NonCopyable {
        private:
            VulkanDevice& device;

        public:
            VulkanDescriptorSetLayout( // Todo move to private
                VulkanDevice& device,
                const std::vector<VulkanDescriptorSetLayoutBinding>& all_bindings);

            ~VulkanDescriptorSetLayout();

            // void destroy(VulkanDevice& device) override;
    };
}

#endif
