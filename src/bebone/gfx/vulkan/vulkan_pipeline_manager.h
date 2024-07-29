#ifndef _BEBONE_VULKAN_PIPELINE_MANAGER_H_
#define _BEBONE_VULKAN_PIPELINE_MANAGER_H_

#include "../gfx_backend.h"

#include "vulkan_device.h"
#include "vulkan_descriptor_pool.h"

namespace bebone::gfx {
    class VulkanConstRange;
    class VulkanPipelineLayout;

    enum class VulkanBindlessBufferHandle : uint32_t { Invalid = 0 };
    enum class VulkanBindlessTextureHandle : uint32_t { Invalid = 0 };

    class VulkanPipelineManager : private core::NonCopyable {
        private:
            std::shared_ptr<VulkanDescriptorPool> descriptor_pool;

            std::shared_ptr<VulkanDescriptorSetLayout> bindless_descriptor_set_layout;
            std::shared_ptr<VulkanDescriptorSet> bindless_descriptor_set;
            std::shared_ptr<VulkanPipelineLayout> bindless_pipeline_layout;

            u32 bindless_uniforms_index;
            u32 bindless_storage_index;
            u32 bindless_samplers_index;

            static constexpr u32 uniform_binding = 0;
            static constexpr u32 storage_binding = 1;
            static constexpr u32 texture_binding = 2;

            static constexpr size_t const_ranges_size = 128;

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

            VulkanBindlessTextureHandle bind_texture(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<VulkanTextureTuple>& texture);

            std::vector<VulkanBindlessTextureHandle> bind_textures(
                std::shared_ptr<VulkanDevice>& device,
                std::vector<std::shared_ptr<VulkanTextureTuple>>& texture);

            VulkanBindlessTextureHandle bind_attachment(
                std::shared_ptr<VulkanDevice>& device,
                std::shared_ptr<IVulkanAttachment>& attachment);

            std::vector<VulkanBindlessTextureHandle> bind_attachments(
                std::shared_ptr<VulkanDevice>& device,
                std::vector<std::shared_ptr<IVulkanAttachment>>& attachments);

            VulkanBindlessBufferHandle bind_uniform_buffer(
                std::shared_ptr<VulkanDevice>& device,
                const std::shared_ptr<VulkanBufferMemoryTuple>& buffer);

            std::vector<VulkanBindlessBufferHandle> bind_uniform_buffers(
                std::shared_ptr<VulkanDevice>& device,
                const std::vector<std::shared_ptr<VulkanBufferMemoryTuple>>& buffers);

            const std::shared_ptr<VulkanDescriptorSet>& get_descriptor_set() const;
            const std::shared_ptr<VulkanDescriptorSetLayout>& get_descriptor_set_layout() const;
            const std::shared_ptr<VulkanPipelineLayout>& get_pipeline_layout() const;

           //  void destroy(VulkanDevice& device) override;
    };
}

#endif
