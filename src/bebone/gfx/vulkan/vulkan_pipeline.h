#ifndef _BEBONE_GFX_VULKAN_PIPELINE_IMPLEMENTATION_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_IMPLEMENTATION_H_

#include "../shaders/shader_code.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_shader_module.h"
#include "vulkan_pipeline_config_info.h"

namespace bebone::gfx {
    class VulkanPipeline : public VulkanWrapper<VkPipeline>, private core::NonCopyable {
        private:
            void create_graphics_pipeline(
                VulkanDevice& device,
                std::shared_ptr<VulkanShaderModule>& vertShaderModule,
                std::shared_ptr<VulkanShaderModule>& fragShaderModule,
                const PipelineConfigInfo& configInfo);

        public:
            VulkanPipeline(
                VulkanDevice& device,
                std::shared_ptr<VulkanShaderModule>& vertShaderModule,
                std::shared_ptr<VulkanShaderModule>& fragShaderModule,
                const PipelineConfigInfo& configInfo);

            void recreate(
                VulkanDevice& device,
                std::shared_ptr<VulkanShaderModule>& vertShaderModule,
                std::shared_ptr<VulkanShaderModule>& fragShaderModule,
                const PipelineConfigInfo& configInfo);

            void bind(VkCommandBuffer commandBuffer);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
