#ifndef _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_LAYOUT_H_

#include "../device_impl.h"
#include "../gfx_backend.h"
#include "../pipeline_layout.h"

namespace bebone::gfx {
    class VulkanPipelineLayout : public PipelineLayout {
        private:
            DeviceImpl& _device;
            VkPipelineLayout pipelineLayout;

        public:
            VulkanPipelineLayout(VkDescriptorSetLayout& descriptorSetLayout, DeviceImpl& device) : _device(device) {

                VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
                pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
                
                pipelineLayoutInfo.setLayoutCount = 1; // This thing should be computed from creatated descriptor sets, for now there is just constants
                pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout; // This thing should be computed from creatated descriptor sets, for now there is just constants

                pipelineLayoutInfo.pushConstantRangeCount = 0;
                pipelineLayoutInfo.pPushConstantRanges = nullptr;

                if(vkCreatePipelineLayout(_device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create pipeline layout");
                }
            }

            VkPipelineLayout get_layout() {
                return pipelineLayout;
            }

            ~VulkanPipelineLayout() {

            }
    };
}

#endif
