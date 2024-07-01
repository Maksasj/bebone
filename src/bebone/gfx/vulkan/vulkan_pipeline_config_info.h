#ifndef _BEBONE_GFX_VULKAN_PIPELINE_CONFIG_INFO_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_CONFIG_INFO_H_

#include <vector>

#include "../gfx_backend.h"

namespace bebone::gfx::vulkan {
    // Todo remake this VulkanPipelineVertexInputStateTuple
    struct VulkanPipelineVertexInputStateTuple {
        std::vector<VkVertexInputBindingDescription> binding_descriptions = {};
        std::vector<VkVertexInputAttributeDescription> attribute_descriptions = {};
    };

    // Todo make this structs noncopyable but also lets resolve gcc compilation warning

    // VkPipelineVertexInputStateCreateInfo
    struct VulkanPipelineVertexInputStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineVertexInputStateCreateFlags flags = 0;

        VulkanPipelineVertexInputStateTuple vertex_descriptions = {};
    };

    // VkPipelineInputAssemblyStateCreateInfo
    struct VulkanPipelineInputAssemblyStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineInputAssemblyStateCreateFlags flags = 0;
        VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        VkBool32 primitive_restart_enable = VK_FALSE;
    };

    // VkPipelineTessellationStateCreateInfo
    struct VulkanPipelineTessellationStateConfig {
        VkStructureType type;
        void* ptr_next;
        VkPipelineTessellationStateCreateFlags flags;
        uint32_t patch_control_points;
    };

    // VkPipelineViewportStateCreateInfo
    struct VulkanPipelineViewportStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineViewportStateCreateFlags flags = 0;
        uint32_t viewport_count = 1;
        VkViewport* ptr_viewports = nullptr;
        uint32_t scissor_count = 1;
        VkRect2D* ptr_scissors = nullptr;
    };

    // VkPipelineRasterizationStateCreateInfo
    struct VulkanPipelineRasterizationStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineRasterizationStateCreateFlags flags = 0;
        VkBool32 depth_clamp_enable = VK_FALSE;
        VkBool32 rasterizer_discard_enable = VK_FALSE;
        VkPolygonMode polygon_mode = VK_POLYGON_MODE_FILL;
        VkCullModeFlags cull_mode = VK_CULL_MODE_BACK_BIT;
        VkFrontFace front_face = VK_FRONT_FACE_COUNTER_CLOCKWISE; // Todo
        VkBool32 depth_bias_enable = VK_FALSE;
        float depth_bias_constant_factor = 0.0f;
        float depth_bias_clamp = 0.0f;
        float depth_bias_slope_factor = 0.0f;
        float line_width = 1.0f;
    };

    // VkPipelineMultisampleStateCreateInfo
    struct VulkanPipelineMultisampleStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineMultisampleStateCreateFlags flags = 0;
        VkSampleCountFlagBits rasterization_samples = VK_SAMPLE_COUNT_1_BIT;
        VkBool32 sample_shading_enable = VK_FALSE;
        float min_sample_shading = 1.0f;
        VkSampleMask* ptr_sample_mask = nullptr;
        VkBool32 alpha_to_coverage_enable = VK_FALSE;
        VkBool32 alpha_to_one_enable = VK_FALSE;
    };
    
    // VkPipelineDepthStencilStateCreateInfo
    struct VulkanPipelineDepthStencilStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineDepthStencilStateCreateFlags flags = 0;
        VkBool32 depth_test_enable = VK_TRUE;
        VkBool32 depth_write_enable = VK_TRUE;
        VkCompareOp depth_compare_op = VK_COMPARE_OP_LESS;
        VkBool32 depth_bounds_test_enable = VK_FALSE;
        VkBool32 stencil_test_enable = VK_FALSE;
        VkStencilOpState front = {};
        VkStencilOpState back = {};
        float min_depth_bounds = 0.0f;
        float max_depth_bounds = 1.0f;
    };

    // VkPipelineColorBlendStateCreateInfo
    struct VulkanPipelineColorBlendStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineColorBlendStateCreateFlags flags = 0;
        VkBool32 logic_op_enable = VK_FALSE;
        VkLogicOp logic_op = VK_LOGIC_OP_COPY;

        std::vector<VkPipelineColorBlendAttachmentState> ptr_attachments = {
            {
                .blendEnable = VK_FALSE,
                .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
                .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
                .colorBlendOp = VK_BLEND_OP_ADD,
                .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
                .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
                .alphaBlendOp = VK_BLEND_OP_ADD,
                .colorWriteMask = (VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT)
            }
        };

        float blend_constants[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    };

    // VkPipelineDynamicStateCreateInfo
    struct VulkanPipelineDynamicStateConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineDynamicStateCreateFlags flags = 0;

        std::vector<VkDynamicState> ptr_dynamic_states = {
            VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR
        };
    };

    struct VulkanPipelineConfig {
        VkStructureType type = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        void* ptr_next = nullptr;
        VkPipelineCreateFlags flags = 0;

        // uint32_t stageCount;                                                     // Stage thing
        // VkPipelineShaderStageCreateInfo* pStages;                                // Stage thing

        VulkanPipelineVertexInputStateConfig vertex_input_state = {};                //
        VulkanPipelineInputAssemblyStateConfig input_assembly_state = {};            //
        VulkanPipelineTessellationStateConfig* ptr_tessellation_state = nullptr;        // For now lets set this to null
        VulkanPipelineViewportStateConfig viewport_state = {};                      //
        VulkanPipelineRasterizationStateConfig rasterization_state = {};            //
        VulkanPipelineMultisampleStateConfig multisample_state = {};                //
        VulkanPipelineDepthStencilStateConfig depth_stencil_state = {};              //
        VulkanPipelineColorBlendStateConfig color_blend_state = {};                  //
        VulkanPipelineDynamicStateConfig dynamic_state = {};                        //

        // VkPipelineLayout layout;                                                 // Pipeline thing
        // VkRenderPass render_pass;                                                 // Pipeline thing

        uint32_t subpass = 0;
        VkPipeline base_pipeline_handle = VK_NULL_HANDLE;
        int32_t base_pipeline_index = -1;
    };
}

#endif
