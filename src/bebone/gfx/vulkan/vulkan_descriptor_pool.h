#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanDescriptorPool {
        private:
            // static constexpr uint32_t maxBindlessResources = 512;
            static constexpr uint32_t maxBindlessResources = 65536;

            VkDescriptorPool descriptorPool;

            std::vector<VkDescriptorSet> descriptorSets;
            std::vector<VkDescriptorSetLayout> descriptorSetLayouts;

        public:
            VulkanDevice& _device;

            // Todo Count should be pre computed 
            VulkanDescriptorPool(VulkanDevice& device);

            ~VulkanDescriptorPool();

            VkDescriptorSetLayout* create_descriptor_set_layout(const std::vector<VkDescriptorSetLayoutBinding>& bindings);

            VkDescriptorSet* create_descriptor_bindless(VkDescriptorSetLayout* descriptorSetLayout);

            VkDescriptorSet* create_descriptor(VkDescriptorSetLayout* descriptorSetLayout, VkBuffer buffer);

            VkDescriptorSet& get_descriptor_set(const size_t& index);

            size_t get_layouts_count() const;

            VkDescriptorSetLayout* get_layouts_data();
    };  
}

#endif
