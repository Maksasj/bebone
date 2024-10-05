#ifndef _BEBONE_GFX_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanDescriptorSet;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorPool : public VulkanWrapper<VkDescriptorPool>, private core::NonCopyable {
        private:
            VulkanDevice& device;

        public:
            VulkanDescriptorPool(VulkanDevice& device);
            ~VulkanDescriptorPool();

            std::shared_ptr<VulkanDescriptorSet> create_descriptor(
                VulkanDevice& device,
                const std::shared_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout);

            std::vector<std::shared_ptr<VulkanDescriptorSet>> create_descriptors(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanDescriptorSetLayout>& descriptor_set_layout,
                const size_t& count);

            // void destroy(VulkanDevice& device) override;
    };  
}

#endif
