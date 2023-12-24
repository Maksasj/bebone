#ifndef BEBONE_VULKAN_DESCRIPTOR_SET
#define BEBONE_VULKAN_DESCRIPTOR_SET

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
                std::shared_ptr<VulkanDevice>& device,
                VulkanDescriptorPool& descriptorPool,
                std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
