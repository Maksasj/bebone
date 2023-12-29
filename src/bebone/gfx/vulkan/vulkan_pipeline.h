#ifndef _BEBONE_GFX_VULKAN_VULKAN_PIPELINE_H_
#define _BEBONE_GFX_VULKAN_VULKAN_PIPELINE_H_

#include "../shaders/shader_code.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_shader_module.h"
#include "vulkan_pipeline_config_info.h"

namespace bebone::gfx {
    class VulkanSwapChain;
    class VulkanShaderModule;
    class VulkanPipelineLayout;

    class VulkanPipeline : public VulkanWrapper<VkPipeline>, private core::NonCopyable {
        private:
         static std::vector<VkPipelineShaderStageCreateInfo> collect_shader_stages(
             std::vector<std::shared_ptr<VulkanShaderModule>>& shaderModules);

        public:
            VulkanPipeline(
                VulkanDevice& device,
                std::shared_ptr<VulkanSwapChain>& swapChain,
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                std::vector<std::shared_ptr<VulkanShaderModule>>& shaderModules,
                VulkanPipelineConfig& configInfo);

            // void recreate(
            //     VulkanDevice& device,
            //     std::shared_ptr<VulkanShaderModule>& vertShaderModule,
            //     std::shared_ptr<VulkanShaderModule>& fragShaderModule,
            //     const PipelineConfigInfo& configInfo);

            void bind(VkCommandBuffer commandBuffer);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
