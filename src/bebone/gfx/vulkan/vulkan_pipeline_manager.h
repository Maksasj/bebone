#ifndef _BEBONE_VULKAN_PIPELINE_MANAGER_H_
#define _BEBONE_VULKAN_PIPELINE_MANAGER_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx {
    class VulkanConstRange;
    class VulkanPipelineLayout;

    class VulkanPipelineManager : public VulkanApi, private core::NonCopyable {
        private:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool;

            std::shared_ptr<VulkanDescriptorSetLayout> bindless_descriptor_set_layout;
            std::shared_ptr<VulkanDescriptorSet> bindless_descriptor_set;
            std::shared_ptr<VulkanPipelineLayout> bindless_pipeline_layout;

        private:
            u32 bindless_uniforms_index;
            u32 bindless_storage_index;
            u32 bindless_samplers_index;

        public:
            VulkanPipelineManager(VulkanDevice& device);

            std::shared_ptr<VulkanPipeline> create_pipeline(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanRenderPass>& render_pass,
                std::shared_ptr<VulkanShaderModule> vertex_shader_module,
                std::shared_ptr<VulkanShaderModule> fragment_shader_module,
                VulkanPipelineConfig config_info
            );

            std::shared_ptr<VulkanPipeline> create_pipeline(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanRenderPass>& render_pass,
                const std::string& vertex_shader_file_path,
                const std::string& fragment_shader_file_path,
                VulkanPipelineConfig config_info
            );

            const std::shared_ptr<VulkanDescriptorSet>& get_descriptor_set() const;
            const std::shared_ptr<VulkanDescriptorSetLayout>& get_descriptor_set_layout() const;

            void destroy(VulkanDevice& device) override;
    };
}

#endif
