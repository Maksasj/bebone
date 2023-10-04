#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"

#include "../vulkan_device.h"

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
            VulkanDescriptorPool(VulkanDevice& device) : _device(device) {
                // If vector resizes, then all pointers to descriptors will not be valid
                
                descriptorSets.reserve(65536);
                descriptorSetLayouts.reserve(65536);


                // Todo Why do we need to set type to specific, i wanned to use this also for ssbo
                std::vector<VkDescriptorPoolSize> poolSizes = {
                    { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, maxBindlessResources },
                    // { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, maxBindlessResources },
                };

                VkDescriptorPoolCreateInfo poolInfo{};
                poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
                poolInfo.poolSizeCount = poolSizes.size();
                poolInfo.pPoolSizes = poolSizes.data();
                poolInfo.maxSets = static_cast<uint32_t>(65536 * poolSizes.size());
                poolInfo.flags = VK_DESCRIPTOR_POOL_CREATE_UPDATE_AFTER_BIND_BIT;

                if (vkCreateDescriptorPool(_device.device(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create descriptor pool!");
                }
            }

            ~VulkanDescriptorPool() {
                for(const auto& layouts : descriptorSetLayouts) {
                    vkDestroyDescriptorSetLayout(_device.device(), layouts, nullptr);
                }

                vkDestroyDescriptorPool(_device.device(), descriptorPool, nullptr);
            }

            VkDescriptorSetLayout* create_descriptor_set_layout(const std::vector<VkDescriptorSetLayoutBinding>& bindings) {
                std::vector<VkDescriptorBindingFlags> bindingFlags;
                
                for(size_t i = 0; i < bindings.size(); ++i) {
                    VkDescriptorBindingFlags bindlessFlags;

                    if(i == bindings.size() - 1) {
                        bindlessFlags = 
                            VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT | 
                            // VK_DESCRIPTOR_BINDING_VARIABLE_DESCRIPTOR_COUNT_BIT_EXT | 
                            VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT;
                    } else {
                        bindlessFlags = 
                            VK_DESCRIPTOR_BINDING_PARTIALLY_BOUND_BIT_EXT | 
                            VK_DESCRIPTOR_BINDING_UPDATE_AFTER_BIND_BIT_EXT;
                    }

                    bindingFlags.push_back(bindlessFlags);
                }

                descriptorSetLayouts.push_back(VkDescriptorSetLayout{});
                VkDescriptorSetLayout &descriptorSetLayout = descriptorSetLayouts[descriptorSetLayouts.size() - 1];

                // Descriptor set
                VkDescriptorSetLayoutCreateInfo layoutInfo{};
                layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
                layoutInfo.bindingCount = bindings.size();
                layoutInfo.pBindings = bindings.data();
                layoutInfo.flags = VK_DESCRIPTOR_SET_LAYOUT_CREATE_UPDATE_AFTER_BIND_POOL_BIT_EXT;

                VkDescriptorSetLayoutBindingFlagsCreateInfoEXT extendedInfo;
                extendedInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_BINDING_FLAGS_CREATE_INFO_EXT;
                extendedInfo.pNext = nullptr;
                extendedInfo.bindingCount = bindingFlags.size();

                if(bindingFlags.size() == 0) {
                    extendedInfo.pBindingFlags = nullptr;                    
                } else
                    extendedInfo.pBindingFlags = bindingFlags.data();

                layoutInfo.pNext = &extendedInfo;
        
                if (vkCreateDescriptorSetLayout(_device.device(), &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create descriptor set layout!");
                }

                return &descriptorSetLayout;
            }

            VkDescriptorSet* create_descriptor_bindless(VkDescriptorSetLayout* descriptorSetLayout) {
                VkDescriptorSetAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
                allocInfo.descriptorPool = descriptorPool;
                allocInfo.descriptorSetCount = 1;
                allocInfo.pSetLayouts = descriptorSetLayout;

                descriptorSets.push_back({});

                VkDescriptorSetVariableDescriptorCountAllocateInfoEXT countInfo;
                countInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_VARIABLE_DESCRIPTOR_COUNT_ALLOCATE_INFO_EXT;
                countInfo.pNext = nullptr;
                
                unsigned int maxBinding = maxBindlessResources - 1;
                countInfo.descriptorSetCount = 1;

                countInfo.pDescriptorCounts = &maxBinding;
                allocInfo.pNext = &countInfo; // Todo

                auto& descriptorSet = descriptorSets[descriptorSets.size() - 1];

                /** Aka taking last */
                if (vkAllocateDescriptorSets(_device.device(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate descriptor sets!");
                }

                return &descriptorSet;
            }

            VkDescriptorSet* create_descriptor(VkDescriptorSetLayout* descriptorSetLayout, VkBuffer buffer) {
                VkDescriptorSetAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
                allocInfo.descriptorPool = descriptorPool;
                allocInfo.descriptorSetCount = 1;
                allocInfo.pSetLayouts = descriptorSetLayout;

                descriptorSets.push_back({});

                auto& descriptorSet = descriptorSets[descriptorSets.size() - 1];

                /** Aka taking last */
                if (vkAllocateDescriptorSets(_device.device(), &allocInfo, &descriptorSet) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate descriptor sets!");
                }

                // So for each  buffer we should create this thing, and update 'descriptorWrite.descriptorCount' and 'descriptorWrite.pBufferInfo'
                VkDescriptorBufferInfo bufferInfo{};
                bufferInfo.buffer = buffer;
                bufferInfo.offset = 0;
                bufferInfo.range = sizeof(float);

                VkWriteDescriptorSet descriptorWrite{};
                descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                descriptorWrite.dstSet = descriptorSet;
                descriptorWrite.dstBinding = 0;
                descriptorWrite.dstArrayElement = 0;
                descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                descriptorWrite.descriptorCount = 1;
                descriptorWrite.pBufferInfo = &bufferInfo;
                descriptorWrite.pImageInfo = nullptr; // Optional
                descriptorWrite.pTexelBufferView = nullptr; // Optional

                vkUpdateDescriptorSets(_device.device(), 1, &descriptorWrite, 0, nullptr);

                return &descriptorSet;
            }

            VkDescriptorSet& get_descriptor_set(const size_t& index) {
                return descriptorSets[index];
            }

            size_t get_layouts_count() const {
                return descriptorSetLayouts.size();
            }

            VkDescriptorSetLayout* get_layouts_data() {
                return descriptorSetLayouts.data();
            }
    };  
}

#endif
