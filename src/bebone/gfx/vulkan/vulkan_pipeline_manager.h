#ifndef _BEBONE_VULKAN_PIPELINE_MANAGER_H_
#define _BEBONE_VULKAN_PIPELINE_MANAGER_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"
#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx {
    class VulkanConstRange;

    class VulkanPipelineManager : public VulkanApi, private core::NonCopyable {
        private:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool;

            std::shared_ptr<VulkanDescriptorSetLayout> bindless_descriptor_set_layout;
            std::shared_ptr<VulkanDescriptorSet> bindless_descriptor_set;

        private:
            u32 bindless_uniforms_index;
            u32 bindless_storage_index;
            u32 bindless_samplers_index;

        public:
            VulkanPipelineManager(VulkanDevice& device);

            VulkanManagedPipelineTuple create_pipeline(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanRenderPass>& render_pass,
                std::shared_ptr<VulkanShaderModule> vertex_shader_module,
                std::shared_ptr<VulkanShaderModule> fragment_shader_module,
                const std::vector<VulkanConstRange>& constant_ranges,
                VulkanPipelineConfig config_info
            );

            VulkanManagedPipelineTuple create_pipeline(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanRenderPass>& render_pass,
                const std::string& vertex_shader_file_path,
                const std::string& fragment_shader_file_path,
                const std::vector<VulkanConstRange>& constant_ranges,
                VulkanPipelineConfig config_info
            );

            void destroy(VulkanDevice& device) override;
    };
}

#endif
