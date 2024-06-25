#include "vulkan_pipeline.h"

#include "vulkan_device.h"
#include "vulkan_swap_chain.h"
#include "vulkan_pipeline_layout.h"

namespace bebone::gfx::vulkan {
    std::vector<VkPipelineShaderStageCreateInfo> VulkanPipeline::collect_shader_stages(std::vector<std::shared_ptr<VulkanShaderModule>>& shader_modules) {
        auto stages = std::vector<VkPipelineShaderStageCreateInfo>{};
        stages.reserve(shader_modules.size());

        for(auto& shader_module : shader_modules) {
            VkPipelineShaderStageCreateInfo stage;

            stage.type = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.ptr_next = nullptr;
            stage.flags = 0;

            if(shader_module->shaderType == ShaderTypes::vertex_shader)
                stage.stage = VK_SHADER_STAGE_VERTEX_BIT;
            else if(shader_module->shaderType == ShaderTypes::fragment_shader)
                stage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

            stage.module = shader_module->backend;
            stage.pName = "main";
            stage.pSpecializationInfo = nullptr;

            stages.push_back(stage);
        }

        return stages;
    }

    VulkanPipeline::VulkanPipeline(
        VulkanDevice& device,
        std::shared_ptr<VulkanSwapChain>& swap_chain,
        std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
        std::vector<std::shared_ptr<VulkanShaderModule>>& shader_modules,
        VulkanPipelineConfig& config_info
    ) {
        // VkPipelineShaderStageCreateInfo
        auto stages = VulkanPipeline::collect_shader_stages(shader_modules);

        // VulkanPipelineVertexInputStateConfig
        VkPipelineVertexInputStateCreateInfo vertex_input_state{};
        vertex_input_state.type = config_info.vertex_input_state.type;
        vertex_input_state.ptr_next = config_info.vertex_input_state.ptr_next;
        vertex_input_state.flags = config_info.vertex_input_state.flags;

        if(config_info.pVertexInputState.vertexDescriptions.binding_descriptions.size() != 0) {
            vertex_input_state.vertexBindingDescriptionCount = config_info.vertex_input_state.vertexDescriptions.binding_descriptions.size();
            vertex_input_state.pVertexBindingDescriptions = config_info.vertex_input_state.vertexDescriptions.binding_descriptions.data();
        } else {
            vertex_input_state.vertexBindingDescriptionCount = 0;
            vertex_input_state.pVertexBindingDescriptions = nullptr;
        }

        if(config_info.pVertexInputState.vertexDescriptions.attribute_descriptions.size() != 0) {
            vertex_input_state.vertexAttributeDescriptionCount = config_info.vertex_input_state.vertexDescriptions.attribute_descriptions.size();
            vertex_input_state.pVertexAttributeDescriptions = config_info.vertex_input_state.vertexDescriptions.attribute_descriptions.data();
        } else {
            vertex_input_state.vertexAttributeDescriptionCount = 0;
            vertex_input_state.pVertexAttributeDescriptions = nullptr;
        }

        // VulkanPipelineInputAssemblyStateConfig
        VkPipelineInputAssemblyStateCreateInfo pInputAssemblyState = {
            .type = config_info.pInputAssemblyState.type,
            .ptr_next = config_info.pInputAssemblyState.ptr_next,
            .flags = config_info.pInputAssemblyState.flags,
            .topology = config_info.pInputAssemblyState.topology,
            .primitive_restart_enable = config_info.pInputAssemblyState.primitive_restart_enable
        };

        // VulkanPipelineViewportStateConfig
        VkPipelineViewportStateCreateInfo pViewportState = {
            .type = config_info.pViewportState.type,
            .ptr_next = config_info.pViewportState.ptr_next,
            .flags = config_info.pViewportState.flags,
            .viewport_count = config_info.pViewportState.viewport_count,
            .ptr_viewports = config_info.pViewportState.ptr_viewports,
            .scissor_count = config_info.pViewportState.scissor_count,
            .ptr_scissors = config_info.pViewportState.ptr_scissors
        };

        // VulkanPipelineRasterizationStateConfig
        VkPipelineRasterizationStateCreateInfo pRasterizationState = {
            .type = config_info.pRasterizationState.type,
            .ptr_next = config_info.pRasterizationState.ptr_next,
            .flags = config_info.pRasterizationState.flags,
            .depth_clamp_enable = config_info.pRasterizationState.depth_clamp_enable,
            .rasterizer_discard_enable = config_info.pRasterizationState.rasterizer_discard_enable,
            .polygon_mode = config_info.pRasterizationState.polygon_mode,
            .cull_mode = config_info.pRasterizationState.cull_mode,
            .front_face = config_info.pRasterizationState.front_face,
            .depth_bias_enable = config_info.pRasterizationState.depth_bias_enable,
            .depth_bias_constant_factor = config_info.pRasterizationState.depth_bias_constant_factor,
            .depth_bias_clamp = config_info.pRasterizationState.depth_bias_clamp,
            .depth_bias_slope_factor = config_info.pRasterizationState.depth_bias_slope_factor,
            .line_width = config_info.pRasterizationState.line_width
        };

        // VulkanPipelineMultisampleStateConfig
        VkPipelineMultisampleStateCreateInfo pMultisampleState = {
            .type = config_info.pMultisampleState.type,
            .ptr_next = config_info.pMultisampleState.ptr_next,
            .flags = config_info.pMultisampleState.flags,
            .rasterization_samples = config_info.pMultisampleState.rasterization_samples,
            .sample_shading_enable = config_info.pMultisampleState.sample_shading_enable,
            .min_sample_shading = config_info.pMultisampleState.min_sample_shading,
            .ptr_sample_mask = config_info.pMultisampleState.ptr_sample_mask,
            .alpha_to_coverage_enable = config_info.pMultisampleState.alpha_to_coverage_enable,
            .alpha_to_one_enable = config_info.pMultisampleState.alpha_to_one_enable
        };

        // VulkanPipelineDepthStencilStateConfig
        VkPipelineDepthStencilStateCreateInfo pDepthStencilState = {
            .type = config_info.pDepthStencilState.type,
            .ptr_next = config_info.pDepthStencilState.ptr_next,
            .flags = config_info.pDepthStencilState.flags,
            .depth_test_enable = config_info.pDepthStencilState.depth_test_enable,
            .depth_write_enable = config_info.pDepthStencilState.depth_write_enable,
            .depth_compare_op = config_info.pDepthStencilState.depth_compare_op,
            .depth_bounds_test_enable = config_info.pDepthStencilState.depth_bounds_test_enable,
            .stencilTestEnable = config_info.pDepthStencilState.stencilTestEnable,
            .front = config_info.pDepthStencilState.front,
            .back = config_info.pDepthStencilState.back,
            .minDepthBounds = config_info.pDepthStencilState.minDepthBounds,
            .maxDepthBounds = config_info.pDepthStencilState.maxDepthBounds
        };

        // VulkanPipelineColorBlendStateConfig
        VkPipelineColorBlendStateCreateInfo pColorBlendState = {
            .type = config_info.pColorBlendState.type,
            .ptr_next = config_info.pColorBlendState.ptr_next,
            .flags = config_info.pColorBlendState.flags,
            .logicOpEnable = config_info.pColorBlendState.logicOpEnable,
            .logicOp = config_info.pColorBlendState.logicOp,
            .attachmentCount = static_cast<uint32_t>(config_info.pColorBlendState.pAttachments.size()),
            .pAttachments = config_info.pColorBlendState.pAttachments.data(),
            .blendConstants = {
                config_info.pColorBlendState.blendConstants[0],
                config_info.pColorBlendState.blendConstants[1],
                config_info.pColorBlendState.blendConstants[2],
                config_info.pColorBlendState.blendConstants[3]
            }
        };

        // VulkanPipelineDynamicStateConfig
        VkPipelineDynamicStateCreateInfo pDynamicState = {
            .type = config_info.pDynamicState.type,
            .ptr_next = config_info.pDynamicState.ptr_next,
            .flags = config_info.pDynamicState.flags,
            .dynamicStateCount = static_cast<uint32_t>(config_info.pDynamicState.pDynamicStates.size()),
            .pDynamicStates = config_info.pDynamicState.pDynamicStates.data()
        };

        VkGraphicsPipelineCreateInfo pipelineInfo{};
        pipelineInfo.type = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.ptr_next = nullptr;
        pipelineInfo.flags = config_info.flags;

        pipelineInfo.stageCount = stages.size();
        pipelineInfo.pStages = stages.data();

        pipelineInfo.vertex_input_state = &vertex_input_state;
        pipelineInfo.pInputAssemblyState = &pInputAssemblyState;
        pipelineInfo.pTessellationState = nullptr;
        pipelineInfo.pViewportState = &pViewportState;
        pipelineInfo.pRasterizationState = &pRasterizationState;
        pipelineInfo.pMultisampleState = &pMultisampleState;
        pipelineInfo.pDepthStencilState = &pDepthStencilState;
        pipelineInfo.pColorBlendState = &pColorBlendState;
        pipelineInfo.pDynamicState = &pDynamicState;

        pipelineInfo.layout = pipeline_layout->get_layout();
        pipelineInfo.renderPass = swap_chain->render_target->render_pass->backend;

        pipelineInfo.subpass = config_info.subpass;
        pipelineInfo.basePipelineIndex = config_info.basePipelineIndex;
        pipelineInfo.basePipelineHandle = config_info.basePipelineHandle;

        if (vkCreateGraphicsPipelines(device.device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &backend) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline");
        }
    }

    /*
    void VulkanPipeline::recreate(
        VulkanDevice& device,
        std::shared_ptr<VulkanShaderModule>& vertShaderModule,
        std::shared_ptr<VulkanShaderModule>& fragShaderModule,
        const PipelineConfigInfo& config_info
    ) {
        // Todo move this
        vkDestroyPipeline(device.device, backend, nullptr);

        create_graphics_pipeline(device, vertShaderModule, fragShaderModule, config_info);
    }
    */

    void VulkanPipeline::bind(VkCommandBuffer command_buffer) {
        vkCmdBindPipeline(command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, backend);
    }

    void VulkanPipeline::destroy(VulkanDevice& device) {
        if(is_destroyed())
            return;

        vkDestroyPipeline(device.device, backend, nullptr);
        
        mark_destroyed();
    }
}
