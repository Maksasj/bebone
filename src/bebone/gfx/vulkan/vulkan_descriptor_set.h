#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_SET_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_SET_H_

#include <memory>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"

namespace bebone::gfx::vulkan {
    class VulkanDevice;
    class VulkanDescriptorPool;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorSet : public VulkanWrapper<VkDescriptorSet>, private core::NonCopyable {
        public:
            VulkanDescriptorSet(
                std::shared_ptr<VulkanDevice>& device,
                VulkanDescriptorPool& descriptorPool,
                std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
