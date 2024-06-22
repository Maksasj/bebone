#ifndef _BEBONE_GFX_VULKAN_VULKAN_PIPELINE_CONFIG_INFO_H_
#define _BEBONE_GFX_VULKAN_VULKAN_PIPELINE_CONFIG_INFO_H_

#include <vector>

#include "../gfx_backend.h"

namespace bebone::gfx::vulkan {
    // Todo remake this VulkanPipelineVertexInputStateTuple
    struct VulkanPipelineVertexInputStateTuple {
        std::vector<VkVertexInputBindingDescription> bindingDescriptions = {};
        std::vector<VkVertexInputAttributeDescription> attributeDescriptions = {};
    };

    // Todo make this structs noncopyable but also lets resolve gcc compilation warning

    // VkPipelineVertexInputStateCreateInfo
    struct VulkanPipelineVertexInputStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineVertexInputStateCreateFlags flags = 0;

        VulkanPipelineVertexInputStateTuple vertexDescriptions = {};
    };

    // VkPipelineInputAssemblyStateCreateInfo
    struct VulkanPipelineInputAssemblyStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineInputAssemblyStateCreateFlags flags = 0;
        VkPrimitiveTopology topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        VkBool32 primitiveRestartEnable = VK_FALSE;
    };

    // VkPipelineTessellationStateCreateInfo
    struct VulkanPipelineTessellationStateConfig {
        VkStructureType sType;
        void* pNext;
        VkPipelineTessellationStateCreateFlags flags;
        uint32_t patchControlPoints;
    };

    // VkPipelineViewportStateCreateInfo
    struct VulkanPipelineViewportStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineViewportStateCreateFlags flags = 0;
        uint32_t viewportCount = 1;
        VkViewport* pViewports = nullptr;
        uint32_t scissorCount = 1;
        VkRect2D* pScissors = nullptr;
    };

    // VkPipelineRasterizationStateCreateInfo
    struct VulkanPipelineRasterizationStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineRasterizationStateCreateFlags flags = 0;
        VkBool32 depthClampEnable = VK_FALSE;
        VkBool32 rasterizerDiscardEnable = VK_FALSE;
        VkPolygonMode polygonMode = VK_POLYGON_MODE_FILL;
        VkCullModeFlags cullMode = VK_CULL_MODE_BACK_BIT;
        VkFrontFace frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        VkBool32 depthBiasEnable = VK_FALSE;
        float depthBiasConstantFactor = 0.0f;
        float depthBiasClamp = 0.0f;
        float depthBiasSlopeFactor = 0.0f;
        float lineWidth = 1.0f;
    };

    // VkPipelineMultisampleStateCreateInfo
    struct VulkanPipelineMultisampleStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineMultisampleStateCreateFlags flags = 0;
        VkSampleCountFlagBits rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
        VkBool32 sampleShadingEnable = VK_FALSE;
        float minSampleShading = 1.0f;
        VkSampleMask* pSampleMask = nullptr;
        VkBool32 alphaToCoverageEnable = VK_FALSE;
        VkBool32 alphaToOneEnable = VK_FALSE;
    };
    
    // VkPipelineDepthStencilStateCreateInfo
    struct VulkanPipelineDepthStencilStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineDepthStencilStateCreateFlags flags = 0;
        VkBool32 depthTestEnable = VK_TRUE;
        VkBool32 depthWriteEnable = VK_TRUE;
        VkCompareOp depthCompareOp = VK_COMPARE_OP_LESS;
        VkBool32 depthBoundsTestEnable = VK_FALSE;
        VkBool32 stencilTestEnable = VK_FALSE;
        VkStencilOpState front = {};
        VkStencilOpState back = {};
        float minDepthBounds = 0.0f;
        float maxDepthBounds = 1.0f;
    };

    // VkPipelineColorBlendStateCreateInfo
    struct VulkanPipelineColorBlendStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineColorBlendStateCreateFlags flags = 0;
        VkBool32 logicOpEnable = VK_FALSE;
        VkLogicOp logicOp = VK_LOGIC_OP_COPY;

        std::vector<VkPipelineColorBlendAttachmentState> pAttachments = {
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

        float blendConstants[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    };

    // VkPipelineDynamicStateCreateInfo
    struct VulkanPipelineDynamicStateConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineDynamicStateCreateFlags flags = 0;

        std::vector<VkDynamicState> pDynamicStates = {
            VK_DYNAMIC_STATE_VIEWPORT, VK_DYNAMIC_STATE_SCISSOR
        };
    };

    struct VulkanPipelineConfig {
        VkStructureType sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        void* pNext = nullptr;
        VkPipelineCreateFlags flags = 0;

        // uint32_t stageCount;                                                     // Stage thing
        // VkPipelineShaderStageCreateInfo* pStages;                                // Stage thing

        VulkanPipelineVertexInputStateConfig pVertexInputState = {};                //
        VulkanPipelineInputAssemblyStateConfig pInputAssemblyState = {};            //
        VulkanPipelineTessellationStateConfig* pTessellationState = nullptr;        // For now lets set this to null
        VulkanPipelineViewportStateConfig pViewportState = {};                      //
        VulkanPipelineRasterizationStateConfig pRasterizationState = {};            //
        VulkanPipelineMultisampleStateConfig pMultisampleState = {};                //
        VulkanPipelineDepthStencilStateConfig pDepthStencilState = {};              //
        VulkanPipelineColorBlendStateConfig pColorBlendState = {};                  //
        VulkanPipelineDynamicStateConfig pDynamicState = {};                        //

        // VkPipelineLayout layout;                                                 // Pipeline thing
        // VkRenderPass renderPass;                                                 // Pipeline thing

        uint32_t subpass = 0;
        VkPipeline basePipelineHandle = VK_NULL_HANDLE;
        int32_t basePipelineIndex = -1;
    };
}

#endif
