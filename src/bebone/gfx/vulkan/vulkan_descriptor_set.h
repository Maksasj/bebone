#ifndef BEBONE_VULKAN_DESCRIPTOR_SET
#define BEBONE_VULKAN_DESCRIPTOR_SET

#include <memory>

#include "../gfx_backend.h"

namespace bebone::gfx {
    class VulkanDevice;
    class VulkanDescriptorPool;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorSet {
        public:
            VkDescriptorSet descriptorSet;

            VulkanDescriptorSet(std::shared_ptr<VulkanDevice>& device,VulkanDescriptorPool& descriptorPool,std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout);
    };
}

#endif
