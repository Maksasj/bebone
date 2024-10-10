#ifndef _BEBONE_GFX_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>
#include <memory>

#include "../gfx_backend.h"

#include "vulkan_swap_chain.h"
#include "vulkan_pipeline.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanCommandBufferPool;
    class VulkanDescriptorSet;

    class VulkanCommandBuffer : private core::NonCopyable {
        public:
            VkCommandBuffer backend;

        private:
            VulkanDevice& device_owner;

        public:
            using Self = VulkanCommandBuffer;

            VulkanCommandBuffer(VulkanDevice& device, VulkanCommandBufferPool& command_buffer_pool);

            Self& begin_record();
            Self& end_record();

            // Swap chain specific begin render pass
            Self& begin_render_pass(const VulkanSwapChain& swap_chain);

            Self& begin_render_pass(
                    const std::unique_ptr<VulkanRenderTarget>& render_target,
                    const std::unique_ptr<VulkanRenderPass>& render_pass,
                    const size_t& frame);

            Self& begin_render_pass(
                const std::unique_ptr<VulkanFramebuffer>& framebuffer,
                const std::unique_ptr<VulkanRenderPass>& render_pass);

            Self& end_render_pass();

            Self& set_viewport(std::unique_ptr<Window>& window);
            Self& set_viewport(const Vec2i& viewport, const f32& min_depth = 0.0f, const f32& max_depth = 1.0f);
            Self& set_viewport(const f32& x, const f32& y, const f32& width, const f32& height, const f32& min_depth = 0.0f, const f32& max_depth = 1.0f);
            Self& set_scissors(const i32& x, const i32& y, const u32& width, const u32& height);

            Self& bind_pipeline(const VulkanPipeline& pipeline);
            Self& bind_pipeline(const std::unique_ptr<VulkanPipeline>& pipeline);

            Self& bind_vertex_buffer(IVulkanBuffer& buffer);
            Self& bind_index_buffer(IVulkanBuffer& buffer);

            Self& bind_descriptor_set(
                    const std::unique_ptr<VulkanPipelineLayout>& pipeline_layout,
                    const std::unique_ptr<VulkanDescriptorSet>& descriptor_set);

            Self& bind_descriptor_set(
                    const std::unique_ptr<VulkanPipelineLayout>& pipeline_layout,
                    const std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets,
                    const size_t& frame);

            Self& bind_descriptor_sets(
                    const std::unique_ptr<VulkanPipelineLayout>& pipeline_layout,
                    const std::vector<std::unique_ptr<VulkanDescriptorSet>>& descriptor_sets);

            Self& push_constant(
                    const std::unique_ptr<VulkanPipelineLayout>& pipeline_layout,
                    const u32& size,
                    const void* ptr);

            Self& push_constant(
                    const std::unique_ptr<VulkanPipelineLayout>& pipeline_layout,
                    const uint32_t& size,
                    const size_t& offset,
                    const void* ptr);

            Self& draw(const size_t& vertex_count);
            Self& draw_indexed(const size_t& vertex_count);
    };
}

#endif
