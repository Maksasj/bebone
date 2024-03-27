#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>
#include <memory>

#include "../gfx_backend.h"

#include "vulkan_wrapper.tpp"
#include "vulkan_swap_chain.h"
#include "vulkan_pipeline.h"

namespace bebone::gfx::vulkan {
    using namespace bebone::core;

    class VulkanDevice;
    class VulkanCommandBufferPool;
    class VulkanDescriptorSet;

    class VulkanCommandBuffer : public VulkanWrapper<VkCommandBuffer>, private core::NonCopyable {
        public:
            VulkanCommandBuffer(
                std::shared_ptr<VulkanDevice>& device,
                VulkanCommandBufferPool& commandBufferPool);

            VulkanCommandBuffer& begin_record();
            VulkanCommandBuffer& end_record();

            VulkanCommandBuffer& begin_render_pass(
                std::shared_ptr<VulkanSwapChain>& swapChain,
                const u32& frameBuffer);

            VulkanCommandBuffer& end_render_pass();

            VulkanCommandBuffer& set_viewport(
                const i32& x,
                const i32& y,
                const u32& width,
                const u32& height);

            VulkanCommandBuffer& bind_pipeline(VulkanPipeline& pipeline);
            VulkanCommandBuffer& bind_pipeline(std::shared_ptr<VulkanPipeline>& pipeline);

            VulkanCommandBuffer& bind_vertex_buffer(std::shared_ptr<VulkanBuffer>& buffer);
            VulkanCommandBuffer& bind_index_buffer(std::shared_ptr<VulkanBuffer>& indexBuffer);

            VulkanCommandBuffer& bind_descriptor_set(
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                std::shared_ptr<VulkanDescriptorSet>& descriptorSet);

            VulkanCommandBuffer& bind_descriptor_set(
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets,
                const size_t& frame);

            VulkanCommandBuffer& bind_descriptor_sets(
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                std::vector<std::shared_ptr<VulkanDescriptorSet>>& descriptorSets);

            VulkanCommandBuffer& push_constant(
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                const uint32_t& size,
                const void* ptr);

            VulkanCommandBuffer& push_constant(
                std::shared_ptr<VulkanPipelineLayout>& pipelineLayout,
                const uint32_t& size,
                const size_t& offset,
                const void* ptr);

            VulkanCommandBuffer& draw(const size_t& vertexCount);
            VulkanCommandBuffer& draw_indexed(const size_t& vertexCount);

            void destroy(VulkanDevice& device) override;
    };
}

#endif
