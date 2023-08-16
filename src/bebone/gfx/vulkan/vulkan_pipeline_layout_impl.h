#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_IMPLEMENTATION_H_

#include "../device_impl.h"
#include "../gfx_backend.h"
#include "../pipeline_layout_impl.h"

#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanPipelineLayoutImpl : public PipelineLayoutImpl {
        private:
            DeviceImpl& _device;
            VkPipelineLayout pipelineLayout;
            std::shared_ptr<VulkanDescriptorPool> _descriptorPool;

        public:
            #if 0
            VulkanPipelineLayoutImpl(DeviceImpl& device, std::shared_ptr<VulkanDescriptorPool>& descriptorPool) : _device(device), _descriptorPool(descriptorPool) {
                VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
                pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

                pipelineLayoutInfo.setLayoutCount = descriptorPool->get_layouts_count(); // This thing should be computed from creatated descriptor sets, for now there is just constants
                pipelineLayoutInfo.pSetLayouts = descriptorPool->get_layouts_data(); // This thing should be computed from creatated descriptor sets, for now there is just constants

                pipelineLayoutInfo.pushConstantRangeCount = 0;
                pipelineLayoutInfo.pPushConstantRanges = nullptr;

                if(vkCreatePipelineLayout(_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create pipeline layout");
                }
            }
            #else
                VulkanPipelineLayoutImpl(DeviceImpl& device, std::shared_ptr<VulkanDescriptorPool>& descriptorPool, VkDescriptorSetLayout& descriptorSetLayout) : _device(device), _descriptorPool(descriptorPool) {

                VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
                pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                
                #if 1
                    pipelineLayoutInfo.setLayoutCount = 1; // This thing should be computed from creatated descriptor sets, for now there is just constants
                    pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout; // This thing should be computed from creatated descriptor sets, for now there is just constants
                #else
                    pipelineLayoutInfo.setLayoutCount = 0; // This thing should be computed from creatated descriptor sets, for now there is just constants
                    pipelineLayoutInfo.pSetLayouts = nullptr; // This thing should be computed from creatated descriptor sets, for now there is just constants
                #endif

                pipelineLayoutInfo.pushConstantRangeCount = 0;
                pipelineLayoutInfo.pPushConstantRanges = nullptr;

                if(vkCreatePipelineLayout(_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create pipeline layout");
                }
            }
            #endif
            VkDescriptorSet& get_descriptor_set(const size_t& index) {
                return _descriptorPool->get_descriptor_set(index);
            }

            VkPipelineLayout get_layout() {
                return pipelineLayout;
            }

            ~VulkanPipelineLayoutImpl() {

            }
    };
}

#endif
