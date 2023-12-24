#include "vulkan_pipeline.h"

#include "vulkan_device.h"

namespace bebone::gfx {
    std::vector<VkVertexInputBindingDescription> get_binding_descriptions() {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions(1);

        bindingDescriptions[0].binding = 0;
        bindingDescriptions[0].stride = sizeof(Vec3f) * 2;
        bindingDescriptions[0].inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescriptions;
    }

    std::vector<VkVertexInputAttributeDescription> get_attribute_descriptions() {
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

    void VulkanPipeline::create_graphics_pipeline(
        VulkanDevice& device,
        std::shared_ptr<VulkanShaderModule>& vertShaderModule,
        std::shared_ptr<VulkanShaderModule>& fragShaderModule,
        const PipelineConfigInfo& configInfo
    ) {
        VkPipelineShaderStageCreateInfo shaderStages[2];
        shaderStages[0].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStages[0].stage = VK_SHADER_STAGE_VERTEX_BIT;
        shaderStages[0].module = vertShaderModule->shader;
        shaderStages[0].pName = "main";
        shaderStages[0].flags = 0;
        shaderStages[0].pNext = nullptr;
        shaderStages[0].pSpecializationInfo = nullptr;
        shaderStages[1].sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        shaderStages[1].stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        shaderStages[1].module = fragShaderModule->shader;
        shaderStages[1].pName = "main";
        shaderStages[1].flags = 0;
        shaderStages[1].pNext = nullptr;
        shaderStages[1].pSpecializationInfo = nullptr;

        auto bindingDescriptions = bebone::gfx::get_binding_descriptions();
        auto attributeDescriptions = bebone::gfx::get_attribute_descriptions();

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

        if (vkCreateGraphicsPipelines(device.device(), VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline");
        } else {
            std::cout << "Created graphics pipeline !\n";
        }
    }

    VulkanPipeline::VulkanPipeline(
        VulkanDevice& device,
        std::shared_ptr<VulkanShaderModule>& vertShaderModule,
        std::shared_ptr<VulkanShaderModule>& fragShaderModule,
        const PipelineConfigInfo& configInfo
    ) {
        create_graphics_pipeline(device, vertShaderModule, fragShaderModule, configInfo);
    }

    void VulkanPipeline::recreate(
        VulkanDevice& device,
        std::shared_ptr<VulkanShaderModule>& vertShaderModule,
        std::shared_ptr<VulkanShaderModule>& fragShaderModule,
        const PipelineConfigInfo& configInfo
    ) {

        vkDestroyPipeline(device.device(), graphicsPipeline, nullptr);

        create_graphics_pipeline(device, vertShaderModule, fragShaderModule, configInfo);
    }

    VulkanPipeline::~VulkanPipeline() {
        // vkDestroyPipeline(device.device(), graphicsPipeline, nullptr);
    }

    void VulkanPipeline::bind(VkCommandBuffer commandBuffer) {
        vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
    }
}
