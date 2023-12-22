#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanDescriptorSet;
    class VulkanDescriptorSetLayout;

    class VulkanDescriptorPool {
        public:
            VkDescriptorPool descriptorPool;

            // std::vector<VkDescriptorSet> descriptorSets;
            // std::vector<VkDescriptorSetLayout> descriptorSetLayouts;

            VulkanDevice& _device;

            // Todo Count should be pre computed 
            VulkanDescriptorPool(VulkanDevice& device);

            ~VulkanDescriptorPool();

            std::shared_ptr<VulkanDescriptorSet> create_descriptor_bindless(std::shared_ptr<VulkanDevice>& device, std::shared_ptr<VulkanDescriptorSetLayout>& descriptorSetLayout);
            // std::shared_ptr<VulkanDescriptorSet> VulkanDescriptorPool::create_descriptor_bindless(std::shared_ptr<VulkanDevice>& device, VkDescriptorSetLayout* descriptorSetLayout);

            // VkDescriptorSet* create_descriptor_bindless(std::shared_ptr<VulkanDevice>& device, VkDescriptorSetLayout* descriptorSetLayout);

            // VkDescriptorSet* create_descriptor(VkDescriptorSetLayout* descriptorSetLayout, VkBuffer buffer);

            void update_descriptor_sets(
                std::shared_ptr<VulkanBufferImpl>& buffer,
                const size_t& size,
                std::shared_ptr<VulkanDescriptorSet>& descriptorSet,
                const size_t& binding,
                const size_t& dstArrayElement
            );

            // VkDescriptorSet& get_descriptor_set(const size_t& index);

            // size_t get_layouts_count() const;

            // VkDescriptorSetLayout* get_layouts_data();
    };  
}

#endif
