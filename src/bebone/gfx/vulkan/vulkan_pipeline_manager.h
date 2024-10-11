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
            VulkanDevice& device_owner;

        private:
            std::unique_ptr<VulkanDescriptorPool> descriptor_pool;

            std::unique_ptr<VulkanDescriptorSetLayout> bindless_descriptor_set_layout;
            std::unique_ptr<VulkanDescriptorSet> bindless_descriptor_set;
            std::unique_ptr<VulkanPipelineLayout> bindless_pipeline_layout;

            u32 bindless_uniforms_index;
            u32 bindless_storage_index;
            u32 bindless_samplers_index;

            static constexpr u32 uniform_binding = 0;
            static constexpr u32 storage_binding = 1;
            static constexpr u32 texture_binding = 2;

            static constexpr size_t const_ranges_size = 128;

        public:
            VulkanPipelineManager(VulkanDevice& device);
            ~VulkanPipelineManager();

            std::unique_ptr<VulkanPipeline> create_pipeline(
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                std::unique_ptr<VulkanShaderModule> vertex_shader_module,
                std::unique_ptr<VulkanShaderModule> fragment_shader_module,
                VulkanPipelineConfig config_info = {});

            std::unique_ptr<VulkanPipeline> create_pipeline(
                const std::unique_ptr<VulkanRenderPass>& render_pass,
                const std::string& vertex_shader_file_path,
                const std::string& fragment_shader_file_path,
                VulkanPipelineConfig config_info = {});

            /*
            VulkanBindlessTextureHandle bind_texture(
                std::unique_ptr<VulkanDevice>& device,
                std::unique_ptr<VulkanTexture>& texture);

            std::vector<VulkanBindlessTextureHandle> bind_textures(
                std::unique_ptr<VulkanDevice>& device,
                std::vector<std::unique_ptr<VulkanTexture>>& texture);

             * Todo lets pass not IVulkanAttachment but rather two objects, IVulkanSampler, IVulkanView
            VulkanBindlessTextureHandle bind_attachment(
                std::unique_ptr<VulkanDevice>& device,
                std::unique_ptr<IVulkanAttachment>& attachment);

            std::vector<VulkanBindlessTextureHandle> bind_attachments(
                std::unique_ptr<VulkanDevice>& device,
                std::vector<std::unique_ptr<IVulkanAttachment>>& attachments);
            */

            VulkanBindlessBufferHandle bind_uniform_buffer(IVulkanBuffer& buffer);

            /*
            std::vector<VulkanBindlessBufferHandle> bind_uniform_buffers(
                std::unique_ptr<VulkanDevice>& device,
                const std::vector<std::unique_ptr<VulkanBufferMemory>>& buffers);
            */

            [[nodiscard]] const std::unique_ptr<VulkanDescriptorSet>& get_descriptor_set() const;
            [[nodiscard]] const std::unique_ptr<VulkanDescriptorSetLayout>& get_descriptor_set_layout() const;
            [[nodiscard]] const std::unique_ptr<VulkanPipelineLayout>& get_pipeline_layout() const;
    };
}

#endif
