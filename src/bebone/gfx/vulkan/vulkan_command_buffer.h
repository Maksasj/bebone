#ifndef _BEBONE_GFX_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>
#include <memory>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_swap_chain.h"
#include "vulkan_pipeline.h"

#include "vulkan_buffer_tuples.h"
#include "vulkan_image_tuples.h"
#include "vulkan_pipeline_tuples.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanCommandBufferPool;
    class VulkanDescriptorSet;

    class VulkanCommandBuffer : public VulkanWrapper<VkCommandBuffer>, private core::NonCopyable {
        public:
            VulkanCommandBuffer(
                std::shared_ptr<VulkanDevice>& device,
                VulkanCommandBufferPool& command_buffer_pool);

            VulkanCommandBuffer& begin_record();
            VulkanCommandBuffer& end_record();

            // Swap chain specific begin render pass
            VulkanCommandBuffer& begin_render_pass(
                const std::shared_ptr<VulkanSwapChain> swap_chain);

            VulkanCommandBuffer& begin_render_pass(
                const std::shared_ptr<VulkanFramebuffer>& framebuffer,
                const std::shared_ptr<VulkanRenderPass>& render_pass,
                const VkExtent2D& extent); // Extent probably could be encapsulated by framebuffer or render_pass

            VulkanCommandBuffer& end_render_pass();

            VulkanCommandBuffer& set_viewport(
                const i32& x,
                const i32& y,
                const u32& width,
                const u32& height);

            VulkanCommandBuffer& bind_pipeline(const VulkanPipeline& pipeline);
            VulkanCommandBuffer& bind_pipeline(const std::shared_ptr<VulkanPipeline>& pipeline);
            VulkanCommandBuffer& bind_managed_pipeline(const VulkanManagedPipelineTuple& tuple, const size_t& frame);

            VulkanCommandBuffer& bind_vertex_buffer(const std::shared_ptr<VulkanBuffer>& tuple);
            VulkanCommandBuffer& bind_vertex_buffer(const VulkanBufferMemoryTuple& tuple);

            VulkanCommandBuffer& bind_index_buffer(const std::shared_ptr<VulkanBuffer>& tuple);
            VulkanCommandBuffer& bind_index_buffer(const VulkanBufferMemoryTuple& tuple);

            VulkanCommandBuffer& bind_descriptor_set(
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
                const std::shared_ptr<VulkanDescriptorSet>& descriptor_set);

            VulkanCommandBuffer& bind_descriptor_set(
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
                const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets,
                const size_t& frame);

            VulkanCommandBuffer& bind_descriptor_sets(
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
                const std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptor_sets);

            VulkanCommandBuffer& push_constant(
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
                const u32& size,
                const void* ptr);

            VulkanCommandBuffer& push_constant(
                const std::shared_ptr<VulkanPipelineLayout>& pipeline_layout,
                const uint32_t& size,
                const size_t& offset,
                const void* ptr);

            VulkanCommandBuffer& draw(const size_t& vertex_count);
            VulkanCommandBuffer& draw_indexed(const size_t& vertex_count);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
