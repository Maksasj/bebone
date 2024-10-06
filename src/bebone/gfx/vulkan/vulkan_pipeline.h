#ifndef _BEBONE_GFX_VULKAN_PIPELINE_H_
#define _BEBONE_GFX_VULKAN_PIPELINE_H_

#include "../shaders/shader_code.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_shader_module.h"
#include "vulkan_pipeline_config_info.h"

namespace bebone::gfx {
    class VulkanSwapChain;
    class VulkanShaderModule;
    class VulkanPipelineLayout;
    class VulkanRenderPass;

    class VulkanPipeline : public VulkanWrapper<VkPipeline>, private core::NonCopyable {
        private:
            VulkanDevice& device_owner;

        protected:
             static std::vector<VkPipelineShaderStageCreateInfo> collect_shader_stages(const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules);

            // Todo recreate method
            void create_pipeline(
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                VulkanPipelineLayout& pipeline_layout,
                const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules,
                VulkanPipelineConfig& config_info);

        public:
            VulkanPipeline(
                VulkanDevice& device,
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                VulkanPipelineLayout& pipeline_layout,
                const std::vector<std::unique_ptr<VulkanShaderModule>>& shader_modules,
                VulkanPipelineConfig config_info);

            VulkanPipeline(
                VulkanDevice& device,
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                VulkanPipelineLayout& pipeline_layout,
                const std::string& vertex_shader_path,
                const std::string& fragment_shader_path,
                VulkanPipelineConfig config_info);

            ~VulkanPipeline();


            void bind(VkCommandBuffer command_buffer);
    };
}

#endif
