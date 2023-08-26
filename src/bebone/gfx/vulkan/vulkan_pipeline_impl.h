#ifndef _BEBONE_GFX_VULKAN_PIPELINE_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_IMPLEMENTATION_H_

#include "../pipeline_impl.h"

#include "vulkan_pipeline_config_info.h"

namespace bebone::gfx {
    class VulkanPipeline : public PipelineImpl {
        private:
            void create_graphics_pipeline(const std::vector<unsigned int>& vertSpirv, const std::vector<unsigned int>& fragSpirv, const PipelineConfigInfo& configInfo) {
                create_shader_module(vertSpirv, &vertShaderModule);
                create_shader_module(fragSpirv, &fragShaderModule);

                VkPipelineShaderStageCreateInfo shaderStages[2];
                shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
                shaderStages[0].module = vertShaderModule;
                shaderStages[0].pName = "main";
                shaderStages[0].flags = 0;
                shaderStages[0].pNext = nullptr;
                shaderStages[0].pSpecializationInfo = nullptr;
                shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
                shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
                shaderStages[1].module = fragShaderModule;
                shaderStages[1].pName = "main";
                shaderStages[1].flags = 0;
                shaderStages[1].pNext = nullptr;
                shaderStages[1].pSpecializationInfo = nullptr;

                auto bindingDescriptions = bebone::gfx::getBindingDescriptions();
                auto attributeDescriptions = bebone::gfx::getAttributeDescriptions();

                VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
                vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
                vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
                vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
                vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
                vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();

                VkGraphicsPipelineCreateInfo pipelineInfo{};
                pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
                pipelineInfo.stageCount = 2;
                pipelineInfo.pStages = shaderStages;
                pipelineInfo.pVertexInputState = &vertexInputInfo;
                pipelineInfo.pInputAssemblyState = &configInfo.inputAssemblyInfo;
                pipelineInfo.pViewportState = &configInfo.viewportInfo;
                pipelineInfo.pRasterizationState = &configInfo.rasterizationInfo;
                pipelineInfo.pMultisampleState = &configInfo.multisampleInfo;
                pipelineInfo.pColorBlendState = &configInfo.colorBlendInfo;
                pipelineInfo.pDepthStencilState = &configInfo.depthStencilInfo;
                pipelineInfo.pDynamicState = &configInfo.dynamicStateInfo;

                pipelineInfo.layout = configInfo.pipelineLayout;
                pipelineInfo.renderPass = configInfo.renderPass;
                pipelineInfo.subpass = configInfo.subpass;

                pipelineInfo.basePipelineIndex = -1;
                pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

                if (vkCreateGraphicsPipelines(device.device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &grapgicsPipeline) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create graphics pipeline");
                } else {
                    std::cout << "Created graphics pipeline !\n";
                }
            }

            void create_shader_module(const std::vector<unsigned int>& code, VkShaderModule* shaderModule) {
                VkShaderModuleCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
                createInfo.codeSize = code.size() * sizeof(unsigned int);
                createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

                if(vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create shader module");
                } 
            }
        public:
            DeviceImpl& device;

            VkPipeline grapgicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;


            VulkanPipeline(DeviceImpl& _device, const std::vector<unsigned int>& vertSpirv, const std::vector<unsigned int>& fragSpirv, const PipelineConfigInfo& configInfo)
                     : device{_device} {
                
                create_graphics_pipeline(vertSpirv, fragSpirv, configInfo);
            }

            ~VulkanPipeline() {
                vkDestroyShaderModule(device.device(), vertShaderModule, nullptr);
                vkDestroyShaderModule(device.device(), fragShaderModule, nullptr);
                vkDestroyPipeline(device.device(), grapgicsPipeline, nullptr);
            }

            void bind(VkCommandBuffer commandBuffer) {
                vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, grapgicsPipeline);
            }
    };
}

#endif
