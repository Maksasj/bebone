#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "vulkan_command_buffer.h"

namespace bebone::gfx {
    class VulkanDescriptorPool {
        public:
            // static constexpr uint32_t maxBindlessResources = 512;
            static constexpr uint32_t maxBindlessResources = 65536;

            VkDescriptorPool descriptorPool;

            std::vector<VkDescriptorSet> descriptorSets;
            std::vector<VkDescriptorSetLayout> descriptorSetLayouts;

            VulkanDevice& _device;

            // Todo Count should be pre computed 
            VulkanDescriptorPool(VulkanDevice& device);

            ~VulkanDescriptorPool();

            VkDescriptorSetLayout* create_descriptor_set_layout(const std::vector<VkDescriptorSetLayoutBinding>& bindings);

            VkDescriptorSet* create_descriptor_bindless(VkDescriptorSetLayout* descriptorSetLayout);

            VkDescriptorSet* create_descriptor(VkDescriptorSetLayout* descriptorSetLayout, VkBuffer buffer);

            void update_descriptor_sets(std::shared_ptr<VulkanBufferImpl>& buffer, const size_t& size, VkDescriptorSet& descriptorSet, const size_t& binding, const size_t& dstArrayElement) {
                VkDescriptorBufferInfo bufferInfo{};
                bufferInfo.buffer = buffer->get_buffer();
                bufferInfo.offset = 0;
                bufferInfo.range = size;

                VkWriteDescriptorSet descriptorWrite{};
                descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;

                descriptorWrite.dstSet = descriptorSet;
                descriptorWrite.dstBinding = binding;
                descriptorWrite.dstArrayElement = dstArrayElement; // Todo THIS IS A HANDLE, and handle counter should work per shader binding, not a cpu binding thing

                descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                descriptorWrite.descriptorCount = 1;
                descriptorWrite.pBufferInfo = &bufferInfo;

                descriptorWrite.pImageInfo = nullptr; // Optional
                descriptorWrite.pTexelBufferView = nullptr; // Optional

                vkUpdateDescriptorSets(_device.device(), 1, &descriptorWrite, 0, nullptr);
            }

            VkDescriptorSet& get_descriptor_set(const size_t& index);

            size_t get_layouts_count() const;

            VkDescriptorSetLayout* get_layouts_data();
    };  
}

#endif
