#ifndef _BEBONE_GFX_VULKAN_PIPELINE_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_IMPLEMENTATION_H_

#include "../shaders/shader_code.h"

#include "vulkan_pipeline_config_info.h"

namespace bebone::gfx {
    static std::vector<VkVertexInputBindingDescription> getBindingDescriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);

        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vec3f) * 2;
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescriptions;
    }

    static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions() {
        std::vector<VkVertexInputAttributeDescription> atrributeDescriptions(2);

        atrributeDescriptions[0].binding = 0;
        atrributeDescriptions[0].location = 0;
        atrributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        atrributeDescriptions[0].offset = 0;

        atrributeDescriptions[1].binding = 0;
        atrributeDescriptions[1].location = 1;
        atrributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        atrributeDescriptions[1].offset = sizeof(Vec3f);

        return atrributeDescriptions;
    }

    class VulkanPipeline {
        private:
            void create_graphics_pipeline(const PipelineConfigInfo& configInfo) {
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

            void create_shader_module(const ShaderCode& code, VkShaderModule* shaderModule) {
                VkShaderModuleCreateInfo createInfo{};
                createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
                createInfo.codeSize = code.get_byte_code().size() * sizeof(unsigned int);
                createInfo.pCode = reinterpret_cast<const uint32_t*>(code.get_byte_code().data());

                if(vkCreateShaderModule(device.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
                    throw std::runtime_error("Failed to create shader module");
                } 
            }
        public:
            VulkanDevice& device;

            VkPipeline grapgicsPipeline;
            VkShaderModule vertShaderModule;
            VkShaderModule fragShaderModule;

            VulkanPipeline(VulkanDevice& _device, const ShaderCode& vertSpirv, const ShaderCode& fragSpirv, const PipelineConfigInfo& configInfo)
                     : device(_device) {
                create_shader_module(vertSpirv, &vertShaderModule);
                create_shader_module(fragSpirv, &fragShaderModule);

                create_graphics_pipeline(configInfo);
            }

            void recreate(const PipelineConfigInfo& configInfo) {
                vkDestroyPipeline(device.device(), grapgicsPipeline, nullptr);

                create_graphics_pipeline(configInfo);
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
