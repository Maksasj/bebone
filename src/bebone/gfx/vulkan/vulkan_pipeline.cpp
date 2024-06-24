#include "vulkan_pipeline.h"

#include "vulkan_device.h"
#include "vulkan_swap_chain.h"
#include "vulkan_pipeline_layout.h"

namespace bebone::gfx::vulkan {
    std::vector<VkPipelineShaderStageCreateInfo> VulkanPipeline::collect_shader_stages(std::vector<std::shared_ptr<VulkanShaderModule>>& shaderModules) {
        std::vector<VkPipelineShaderStageCreateInfo> pStages;

        for(auto& shaderModule : shaderModules) {
            VkPipelineShaderStageCreateInfo stage;

            stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.pNext = nullptr;
            stage.flags = 0;

            if(shaderModule->shaderType == ShaderTypes::VERTEX_SHADER)
                stage.stage = VK_SHADER_STAGE_VERTEX_BIT;
            else if(shaderModule->shaderType == ShaderTypes::FRAGMENT_SHADER)
                stage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

            stage.module = shaderModule->backend;
            stage.pName = "main";
            stage.pSpecializationInfo = nullptr;

            pStages.push_back(stage);
        }

        return pStages;
    }

    VulkanPipeline::VulkanPipeline(
            VulkanDevice& device,
            std::shared_ptr<VulkanSwapChain>& swapChain,
            std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
            std::vector<std::shared_ptr<VulkanShaderModule>>& shaderModules,
            VulkanPipelineConfig& configInfo
        ) {

        // VkPipelineShaderStageCreateInfo
        auto pStages = VulkanPipeline::collect_shader_stages(shaderModules);

        // VulkanPipelineVertexInputStateConfig
        VkPipelineVertexInputStateCreateInfo pVertexInputState{};
        pVertexInputState.sType = configInfo.pVertexInputState.sType;
        pVertexInputState.pNext = configInfo.pVertexInputState.pNext;
        pVertexInputState.flags = configInfo.pVertexInputState.flags;

        if(configInfo.pVertexInputState.vertexDescriptions.bindingDescriptions.size() != 0) {
            pVertexInputState.vertexBindingDescriptionCount = configInfo.pVertexInputState.vertexDescriptions.bindingDescriptions.size();
            pVertexInputState.pVertexBindingDescriptions = configInfo.pVertexInputState.vertexDescriptions.bindingDescriptions.data();
        } else {
            pVertexInputState.vertexBindingDescriptionCount = 0;
            pVertexInputState.pVertexBindingDescriptions = nullptr;
        }

        if(configInfo.pVertexInputState.vertexDescriptions.attributeDescriptions.size() != 0) {
            pVertexInputState.vertexAttributeDescriptionCount = configInfo.pVertexInputState.vertexDescriptions.attributeDescriptions.size();
            pVertexInputState.pVertexAttributeDescriptions = configInfo.pVertexInputState.vertexDescriptions.attributeDescriptions.data();
        } else {
            pVertexInputState.vertexAttributeDescriptionCount = 0;
            pVertexInputState.pVertexAttributeDescriptions = nullptr;
        }

        // VulkanPipelineInputAssemblyStateConfig
        VkPipelineInputAssemblyStateCreateInfo pInputAssemblyState = {
            .sType = configInfo.pInputAssemblyState.sType,
            .pNext = configInfo.pInputAssemblyState.pNext,
            .flags = configInfo.pInputAssemblyState.flags,
            .topology = configInfo.pInputAssemblyState.topology,
            .primitiveRestartEnable = configInfo.pInputAssemblyState.primitiveRestartEnable
        };

        // VulkanPipelineViewportStateConfig
        VkPipelineViewportStateCreateInfo pViewportState = {
            .sType = configInfo.pViewportState.sType,
            .pNext = configInfo.pViewportState.pNext,
            .flags = configInfo.pViewportState.flags,
            .viewportCount = configInfo.pViewportState.viewportCount,
            .pViewports = configInfo.pViewportState.pViewports,
            .scissorCount = configInfo.pViewportState.scissorCount,
            .pScissors = configInfo.pViewportState.pScissors
        };

        // VulkanPipelineRasterizationStateConfig
        VkPipelineRasterizationStateCreateInfo pRasterizationState = {
            .sType = configInfo.pRasterizationState.sType,
            .pNext = configInfo.pRasterizationState.pNext,
            .flags = configInfo.pRasterizationState.flags,
            .depthClampEnable = configInfo.pRasterizationState.depthClampEnable,
            .rasterizerDiscardEnable = configInfo.pRasterizationState.rasterizerDiscardEnable,
            .polygonMode = configInfo.pRasterizationState.polygonMode,
            .cullMode = configInfo.pRasterizationState.cullMode,
            .frontFace = configInfo.pRasterizationState.frontFace,
            .depthBiasEnable = configInfo.pRasterizationState.depthBiasEnable,
            .depthBiasConstantFactor = configInfo.pRasterizationState.depthBiasConstantFactor,
            .depthBiasClamp = configInfo.pRasterizationState.depthBiasClamp,
            .depthBiasSlopeFactor = configInfo.pRasterizationState.depthBiasSlopeFactor,
            .lineWidth = configInfo.pRasterizationState.lineWidth
        };

        // VulkanPipelineMultisampleStateConfig
        VkPipelineMultisampleStateCreateInfo pMultisampleState = {
            .sType = configInfo.pMultisampleState.sType,
            .pNext = configInfo.pMultisampleState.pNext,
            .flags = configInfo.pMultisampleState.flags,
            .rasterizationSamples = configInfo.pMultisampleState.rasterizationSamples,
            .sampleShadingEnable = configInfo.pMultisampleState.sampleShadingEnable,
            .minSampleShading = configInfo.pMultisampleState.minSampleShading,
            .pSampleMask = configInfo.pMultisampleState.pSampleMask,
            .alphaToCoverageEnable = configInfo.pMultisampleState.alphaToCoverageEnable,
            .alphaToOneEnable = configInfo.pMultisampleState.alphaToOneEnable
        };

        // VulkanPipelineDepthStencilStateConfig
        VkPipelineDepthStencilStateCreateInfo pDepthStencilState = {
            .sType = configInfo.pDepthStencilState.sType,
            .pNext = configInfo.pDepthStencilState.pNext,
            .flags = configInfo.pDepthStencilState.flags,
            .depthTestEnable = configInfo.pDepthStencilState.depthTestEnable,
            .depthWriteEnable = configInfo.pDepthStencilState.depthWriteEnable,
            .depthCompareOp = configInfo.pDepthStencilState.depthCompareOp,
            .depthBoundsTestEnable = configInfo.pDepthStencilState.depthBoundsTestEnable,
            .stencilTestEnable = configInfo.pDepthStencilState.stencilTestEnable,
            .front = configInfo.pDepthStencilState.front,
            .back = configInfo.pDepthStencilState.back,
            .minDepthBounds = configInfo.pDepthStencilState.minDepthBounds,
            .maxDepthBounds = configInfo.pDepthStencilState.maxDepthBounds
        };

        // VulkanPipelineColorBlendStateConfig
        VkPipelineColorBlendStateCreateInfo pColorBlendState = {
            .sType = configInfo.pColorBlendState.sType,
            .pNext = configInfo.pColorBlendState.pNext,
            .flags = configInfo.pColorBlendState.flags,
            .logicOpEnable = configInfo.pColorBlendState.logicOpEnable,
            .logicOp = configInfo.pColorBlendState.logicOp,
            .attachmentCount = static_cast<uint32_t>(configInfo.pColorBlendState.pAttachments.size()),
            .pAttachments = configInfo.pColorBlendState.pAttachments.data(),
            .blendConstants = {
                configInfo.pColorBlendState.blendConstants[0],
                configInfo.pColorBlendState.blendConstants[1],
                configInfo.pColorBlendState.blendConstants[2],
                configInfo.pColorBlendState.blendConstants[3]
            }
        };

        // VulkanPipelineDynamicStateConfig
        VkPipelineDynamicStateCreateInfo pDynamicState = {
            .sType = configInfo.pDynamicState.sType,
            .pNext = configInfo.pDynamicState.pNext,
            .flags = configInfo.pDynamicState.flags,
            .dynamicStateCount = static_cast<uint32_t>(configInfo.pDynamicState.pDynamicStates.size()),
            .pDynamicStates = configInfo.pDynamicState.pDynamicStates.data()
        };

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.pNext = nullptr;
        pipelineInfo.flags = configInfo.flags;

        pipelineInfo.stageCount = pStages.size();
        pipelineInfo.pStages = pStages.data();

        pipelineInfo.pVertexInputState = &pVertexInputState;
        pipelineInfo.pInputAssemblyState = &pInputAssemblyState;
        pipelineInfo.pTessellationState = nullptr;
        pipelineInfo.pViewportState = &pViewportState;
        pipelineInfo.pRasterizationState = &pRasterizationState;
        pipelineInfo.pMultisampleState = &pMultisampleState;
        pipelineInfo.pDepthStencilState = &pDepthStencilState;
        pipelineInfo.pColorBlendState = &pColorBlendState;
        pipelineInfo.pDynamicState = &pDynamicState;

        pipelineInfo.layout = pipelineLayout->get_layout();
        pipelineInfo.renderPass = swapChain->renderTarget->renderPass->backend;

        pipelineInfo.subpass = configInfo.subpass;
        pipelineInfo.basePipelineIndex = configInfo.basePipelineIndex;
        pipelineInfo.basePipelineHandle = configInfo.basePipelineHandle;

        if (vkCreateGraphicsPipelines(device.device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline");
        }
    }

    /*
    void VulkanPipeline::recreate(
        VulkanDevice& device,
        std::shared_ptr<VulkanShaderModule>& vertShaderModule,
        std::shared_ptr<VulkanShaderModule>& fragShaderModule,
        const PipelineConfigInfo& configInfo
    ) {
        // Todo move this
        vkDestroyPipeline(device.device(), backend, nullptr);

        create_graphics_pipeline(device, vertShaderModule, fragShaderModule, configInfo);
    }
    */

    void VulkanPipeline::bind(VkCommandBuffer commandBuffer) {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, backend);
    }

    void VulkanPipeline::destroy(VulkanDevice& device) {
        vkDestroyPipeline(device.device(), backend, nullptr);
        
        mark_destroyed();
    }
}
