#ifndef _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_
#define _BEBONE_GFX_VULKAN_VULKAN_DESCRIPTOR_POOL_H_

#include <vector>

#include "../gfx_backend.h"
#include "../command_buffer_pool.h"

#include "../device_impl.h"

#include "vulkan_command_buffer.h"

#include "vulkan_uniform_buffer_pool.h"

namespace bebone::gfx {
    class VulkanDescriptorPool : public DescriptorPool {
        private:
            DeviceImpl& _device;

            VkDescriptorPool descriptorPool;
            std::vector<VkDescriptorSet> descriptorSets;

        public:
            VulkanDescriptorPool(VkDescriptorSetLayout descriptorSetLayout, DeviceImpl& device, const size_t& descriptorPoolCount, VulkanUniformBufferPool& uniformBufferPool) : _device(device) {
                VkDescriptorPoolSize poolSize{};
                poolSize.type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                poolSize.descriptorCount = static_cast<uint32_t>(descriptorPoolCount);

                VkDescriptorPoolCreateInfo poolInfo{};
                poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
                poolInfo.poolSizeCount = 1;
                poolInfo.pPoolSizes = &poolSize;
                poolInfo.maxSets = static_cast<uint32_t>(descriptorPoolCount);

                if (vkCreateDescriptorPool(_device.device(), &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create descriptor pool!");
                }

                std::vector<VkDescriptorSetLayout> layouts(descriptorPoolCount, descriptorSetLayout);
                VkDescriptorSetAllocateInfo allocInfo{};
                allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
                allocInfo.descriptorPool = descriptorPool;
                allocInfo.descriptorSetCount = static_cast<uint32_t>(descriptorPoolCount);
                allocInfo.pSetLayouts = layouts.data();
                
                descriptorSets.resize(descriptorPoolCount);
                if (vkAllocateDescriptorSets(_device.device(), &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
                    throw std::runtime_error("failed to allocate descriptor sets!");
                }

                for(size_t i = 0; i < descriptorPoolCount; i++) {
                    VkDescriptorBufferInfo bufferInfo{};
                    bufferInfo.buffer = uniformBufferPool.uniformBuffers[i]->get_buffer();
                    bufferInfo.offset = 0;
                    bufferInfo.range = sizeof(float);

                    VkWriteDescriptorSet descriptorWrite{};
                    descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
                    descriptorWrite.dstSet = descriptorSets[i];
                    descriptorWrite.dstBinding = 0;
                    descriptorWrite.dstArrayElement = 0;
                    descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
                    descriptorWrite.descriptorCount = 1;
                    descriptorWrite.pBufferInfo = &bufferInfo;
                    descriptorWrite.pImageInfo = nullptr; // Optional
                    descriptorWrite.pTexelBufferView = nullptr; // Optional

                    vkUpdateDescriptorSets(_device.device(), 1, &descriptorWrite, 0, nullptr);
                }
            }

            VkDescriptorSet& get_descriptor_set(const size_t& index) override {
                return descriptorSets[index];
            }

            ~VulkanDescriptorPool() {
                vkDestroyDescriptorPool(_device.device(), descriptorPool, nullptr);
            }
    };  
}

#endif
