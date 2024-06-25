#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx::vulkan {
    class VulkanDescriptorSet;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorPool : public VulkanWrapper<VkDescriptorPool>, private core::NonCopyable {
        public:
            VulkanDescriptorPool(VulkanDevice& device); // Todo, hide this constructor

            std::shared_ptr<VulkanDescriptorSet> create_descriptor(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout);

            std::vector<std::shared_ptr<VulkanDescriptorSet>> create_descriptors(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout,
                const size_t& descriptorCount);

            // Todo Hey any update_descriptor_set functions can be made static ?, nice !


            void destroy(VulkanDevice& device) override;
    };  
}

#endif
