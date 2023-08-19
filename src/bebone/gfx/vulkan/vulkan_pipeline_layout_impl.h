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
            VulkanDescriptorPool& _descriptorPool;
            VkPipelineLayout pipelineLayout;

        public:
            VulkanPipelineLayoutImpl(DeviceImpl& device, VulkanDescriptorPool& descriptorPool) : _device(device), _descriptorPool(descriptorPool) {
                VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
                pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

                std::vector<VkPushConstantRange> pushConstantRanges;

                {
                    VkPushConstantRange pushConstant;
                    pushConstant.offset = 0;
                    pushConstant.size = sizeof(unsigned int);
                    pushConstant.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;

                    pushConstantRanges.push_back(pushConstant);
                }

                pipelineLayoutInfo.setLayoutCount = descriptorPool.get_layouts_count(); // This thing should be computed from creatated descriptor sets, for now there is just constants
                pipelineLayoutInfo.pSetLayouts = descriptorPool.get_layouts_data(); // This thing should be computed from creatated descriptor sets, for now there is just constants
                pipelineLayoutInfo.pushConstantRangeCount = pushConstantRanges.size();
                pipelineLayoutInfo.pPushConstantRanges = pushConstantRanges.data();

                if(vkCreatePipelineLayout(_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create pipeline layout");
                }
            }

            VkPipelineLayout get_layout() {
                return pipelineLayout;
            }

            ~VulkanPipelineLayoutImpl() {

            }
    };
}

#endif
