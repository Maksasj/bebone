#include "vulkan_pipeline.h"

#include "vulkan_device.h"
#include "vulkan_swap_chain.h"
#include "vulkan_pipeline_layout.h"

namespace bebone::gfx {
    std::vector<VkPipelineShaderStageCreateInfo> VulkanPipeline::collect_shader_stages(const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules) {
        auto stages = std::vector<VkPipelineShaderStageCreateInfo>{};
        stages.reserve(shader_modules.size());

        for(auto& shader_module : shader_modules) {
            VkPipelineShaderStageCreateInfo stage;

            stage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
            stage.pNext = nullptr;
            stage.flags = 0;
            stage.module = shader_module->backend;
            stage.pName = "main";
            stage.pSpecializationInfo = nullptr;

            if(shader_module->type == ShaderType::VertexShader)
                stage.stage = VK_SHADER_STAGE_VERTEX_BIT;
            else if(shader_module->type == ShaderType::FragmentShader)
                stage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;

            stages.push_back(stage);
        }

        return stages;
    }

    void VulkanPipeline::create_pipeline(
        const std::unique_ptr<VulkanRenderPass>& render_pass,
        VulkanPipelineLayout& pipeline_layout,
        const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules,
        VulkanPipelineConfig& config_info
    ) {
        // VkPipelineShaderStageCreateInfo
        auto stages = VulkanPipeline::collect_shader_stages(shader_modules);

        // VulkanPipelineVertexInputStateConfig
        VkPipelineVertexInputStateCreateInfo vertex_input_state{};
        vertex_input_state.sType = config_info.vertex_input_state.type;
        vertex_input_state.pNext = config_info.vertex_input_state.ptr_next;
        vertex_input_state.flags = config_info.vertex_input_state.flags;

        if(!config_info.vertex_input_state.vertex_descriptions.binding_descriptions.empty()) {
            vertex_input_state.vertexBindingDescriptionCount = config_info.vertex_input_state.vertex_descriptions.binding_descriptions.size();
            vertex_input_state.pVertexBindingDescriptions = config_info.vertex_input_state.vertex_descriptions.binding_descriptions.data();
        } else {
            vertex_input_state.vertexBindingDescriptionCount = 0;
            vertex_input_state.pVertexBindingDescriptions = nullptr;
        }

        if(!config_info.vertex_input_state.vertex_descriptions.attribute_descriptions.empty()) {
            vertex_input_state.vertexAttributeDescriptionCount = config_info.vertex_input_state.vertex_descriptions.attribute_descriptions.size();
            vertex_input_state.pVertexAttributeDescriptions = config_info.vertex_input_state.vertex_descriptions.attribute_descriptions.data();
        } else {
            vertex_input_state.vertexAttributeDescriptionCount = 0;
            vertex_input_state.pVertexAttributeDescriptions = nullptr;
        }

        // VulkanPipelineInputAssemblyStateConfig
        const VkPipelineInputAssemblyStateCreateInfo input_assembly_state = {
                .sType = config_info.input_assembly_state.type,
                .pNext = config_info.input_assembly_state.ptr_next,
                .flags = config_info.input_assembly_state.flags,
                .topology = config_info.input_assembly_state.topology,
                .primitiveRestartEnable = config_info.input_assembly_state.primitive_restart_enable
        };

        // Static scissors
        const auto scissors = VkRect2D {
                { 0, 0 },
                { render_pass->get_extent().width, render_pass->get_extent().height }
        };

        // VulkanPipelineViewportStateConfig
        const VkPipelineViewportStateCreateInfo viewport_state = {
                .sType = config_info.viewport_state.type,
                .pNext = config_info.viewport_state.ptr_next,
                .flags = config_info.viewport_state.flags,
                .viewportCount = config_info.viewport_state.viewport_count,
                .pViewports = config_info.viewport_state.ptr_viewports,
                .scissorCount = 1,
                .pScissors = &scissors
        };

        // VulkanPipelineRasterizationStateConfig
        const VkPipelineRasterizationStateCreateInfo rasterization_state = {
                .sType = config_info.rasterization_state.type,
                .pNext = config_info.rasterization_state.ptr_next,
                .flags = config_info.rasterization_state.flags,
                .depthClampEnable = config_info.rasterization_state.depth_clamp_enable,
                .rasterizerDiscardEnable = config_info.rasterization_state.rasterizer_discard_enable,
                .polygonMode = config_info.rasterization_state.polygon_mode,
                .cullMode = config_info.rasterization_state.cull_mode,
                .frontFace = config_info.rasterization_state.front_face,
                .depthBiasEnable = config_info.rasterization_state.depth_bias_enable,
                .depthBiasConstantFactor = config_info.rasterization_state.depth_bias_constant_factor,
                .depthBiasClamp = config_info.rasterization_state.depth_bias_clamp,
                .depthBiasSlopeFactor = config_info.rasterization_state.depth_bias_slope_factor,
                .lineWidth = config_info.rasterization_state.line_width
        };

        // VulkanPipelineMultisampleStateConfig
        const VkPipelineMultisampleStateCreateInfo multisample_state = {
                .sType = config_info.multisample_state.type,
                .pNext = config_info.multisample_state.ptr_next,
                .flags = config_info.multisample_state.flags,
                .rasterizationSamples = config_info.multisample_state.rasterization_samples,
                .sampleShadingEnable = config_info.multisample_state.sample_shading_enable,
                .minSampleShading = config_info.multisample_state.min_sample_shading,
                .pSampleMask = config_info.multisample_state.ptr_sample_mask,
                .alphaToCoverageEnable = config_info.multisample_state.alpha_to_coverage_enable,
                .alphaToOneEnable = config_info.multisample_state.alpha_to_one_enable
        };

        // VulkanPipelineDepthStencilStateConfig
        const VkPipelineDepthStencilStateCreateInfo depth_stencil_state = {
                .sType = config_info.depth_stencil_state.type,
                .pNext = config_info.depth_stencil_state.ptr_next,
                .flags = config_info.depth_stencil_state.flags,
                .depthTestEnable = config_info.depth_stencil_state.depth_test_enable,
                .depthWriteEnable = config_info.depth_stencil_state.depth_write_enable,
                .depthCompareOp = config_info.depth_stencil_state.depth_compare_op,
                .depthBoundsTestEnable = config_info.depth_stencil_state.depth_bounds_test_enable,
                .stencilTestEnable = config_info.depth_stencil_state.stencil_test_enable,
                .front = config_info.depth_stencil_state.front,
                .back = config_info.depth_stencil_state.back,
                .minDepthBounds = config_info.depth_stencil_state.min_depth_bounds,
                .maxDepthBounds = config_info.depth_stencil_state.max_depth_bounds
        };

        // Todo fix this cringe,
        auto g = config_info.color_blend_state.ptr_attachments[0];
        config_info.color_blend_state.ptr_attachments.clear();
        for(size_t i = 0; i < render_pass->get_color_attachments_count(); ++i)
            config_info.color_blend_state.ptr_attachments.push_back(g);

        // VulkanPipelineColorBlendStateConfig
        const VkPipelineColorBlendStateCreateInfo color_blend_state = {
                .sType = config_info.color_blend_state.type,
                .pNext = config_info.color_blend_state.ptr_next,
                .flags = config_info.color_blend_state.flags,
                .logicOpEnable = config_info.color_blend_state.logic_op_enable,
                .logicOp = config_info.color_blend_state.logic_op,

                // Todo, since we have may have multiple color attachments, that means that this also should be computed
                .attachmentCount = static_cast<uint32_t>(config_info.color_blend_state.ptr_attachments.size()),
                .pAttachments = config_info.color_blend_state.ptr_attachments.data(),

                .blendConstants = {
                        config_info.color_blend_state.blend_constants[0],
                        config_info.color_blend_state.blend_constants[1],
                        config_info.color_blend_state.blend_constants[2],
                        config_info.color_blend_state.blend_constants[3]
                }
        };

        // VulkanPipelineDynamicStateConfig
        const VkPipelineDynamicStateCreateInfo dynamic_state = {
                .sType = config_info.dynamic_state.type,
                .pNext = config_info.dynamic_state.ptr_next,
                .flags = config_info.dynamic_state.flags,
                .dynamicStateCount = static_cast<uint32_t>(config_info.dynamic_state.ptr_dynamic_states.size()),
                .pDynamicStates = config_info.dynamic_state.ptr_dynamic_states.data()
        };

        const auto size = static_cast<uint32_t>(stages.size());

        const VkGraphicsPipelineCreateInfo pipeline_info = {
                .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
                .pNext = nullptr,
                .flags = config_info.flags,

                .stageCount = size,
                .pStages = stages.data(),

                .pVertexInputState = &vertex_input_state,
                .pInputAssemblyState = &input_assembly_state,
                .pTessellationState = nullptr,
                .pViewportState = &viewport_state,
                .pRasterizationState = &rasterization_state,
                .pMultisampleState = &multisample_state,
                .pDepthStencilState = &depth_stencil_state,
                .pColorBlendState = &color_blend_state,
                .pDynamicState = &dynamic_state,

                .layout = pipeline_layout.backend,
                .renderPass = render_pass->backend, // Todo, actually swap chain is not needed there

                .subpass = config_info.subpass,
                .basePipelineHandle = config_info.base_pipeline_handle,
                .basePipelineIndex = config_info.base_pipeline_index
        };

        if(vkCreateGraphicsPipelines(device_owner.device, VK_NULL_HANDLE, 1, &pipeline_info, nullptr, &backend) != VK_SUCCESS) {
            LOG_ERROR("Failed to create graphics pipeline");
            throw std::runtime_error("failed to create graphics pipeline");
        }

        LOG_TRACE("Created Vulkan graphics pipeline");
    }

    VulkanPipeline::VulkanPipeline(
        VulkanDevice& device,
        const std::unique_ptr<VulkanRenderPass>& render_pass,
        VulkanPipelineLayout& pipeline_layout,
        const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules,
        VulkanPipelineConfig config_info
    ) : device_owner(device) {
        create_pipeline(render_pass, pipeline_layout, shader_modules, config_info);
    }

    VulkanPipeline::VulkanPipeline(
        VulkanDevice& device,
        const std::unique_ptr<VulkanRenderPass>& render_pass,
        VulkanPipelineLayout& pipeline_layout,
        const std::string& vertex_shader_path,
        const std::string& fragment_shader_path,
        VulkanPipelineConfig config_info
    ) : device_owner(device) {
        std::vector<std::unique_ptr<VulkanShaderModule>> shader_modules;
        shader_modules.push_back(device.create_shader_module(utils_read_file(vertex_shader_path), ShaderType::VertexShader));
        shader_modules.push_back(device.create_shader_module(utils_read_file(fragment_shader_path), ShaderType::FragmentShader));

        create_pipeline(render_pass, pipeline_layout, shader_modules, config_info);
    }

    VulkanPipeline::~VulkanPipeline() {
        vkDestroyPipeline(device_owner.device, backend, nullptr);

        LOG_TRACE("Destroyed Vulkan graphics pipeline");
    }

    /*
    void VulkanPipeline::recreate(
        VulkanDevice& device,
        std::unique_ptr<VulkanShaderModule>& vertShaderModule,
        std::unique_ptr<VulkanShaderModule>& fragShaderModule,
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
}
