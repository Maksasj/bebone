#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_SET_H_

#include <memory>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx {
    class VulkanDevice;
    class VulkanDescriptorPool;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorSet : public VulkanWrapper<VkDescriptorSet>, private core::NonCopyable {
        public:
            VulkanDescriptorSet(
                VulkanDevice& device,
                VulkanDescriptorPool& descriptor_pool,
                const std::shared_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
