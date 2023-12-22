#ifndef BEBONE_VULKAN_DESCRIPTOR_SET
#define BEBONE_VULKAN_DESCRIPTOR_SET

#include "../gfx_backend.h"

namespace bebone::gfx {
    class VulkanDevice;
    class VulkanDescriptorPool;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorSet {
        public:
            VkDescriptorSet descriptorSet;

            static constexpr uint32_t maxBindlessResources = 65536;

            VulkanDescriptorSet(
                std::shared_ptr<VulkanDevice> device,
                VulkanDescriptorPool& descriptorPool,
                std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout
            );
    };
}

#endif
