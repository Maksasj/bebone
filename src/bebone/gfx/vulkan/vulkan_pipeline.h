#ifndef _BEBONE_GFX_VULKAN_PIPELINE_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_H_

#include "../shaders/shader_code.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_shader_module.h"
#include "vulkan_pipeline_config_info.h"

namespace bebone::gfx::vulkan {
    class VulkanSwapChain;
    class VulkanShaderModule;
    class VulkanPipelineLayout;

    class VulkanPipeline : public VulkanWrapper<VkPipeline>, private core::NonCopyable {
        private:
             static std::vector<VkPipelineShaderStageCreateInfo> collect_shader_stages(
                 const std::vector<std::shared_ptr<VulkanShaderModule>>& shader_modules);

        public:
            VulkanPipeline(
                VulkanDevice& device,
                const std::shared_ptr<VulkanSwapChain>& swap_chain,
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
                const std::vector<std::shared_ptr<VulkanShaderModule>>& shader_modules,
                VulkanPipelineConfig& config_info);

            // void recreate(
            //     VulkanDevice& device,
            //     std::shared_ptr<VulkanShaderModule>& vertShaderModule,
            //     std::shared_ptr<VulkanShaderModule>& fragShaderModule,
            //     const PipelineConfigInfo& config_info);

            void bind(VkCommandBuffer command_buffer);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
