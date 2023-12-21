#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>

#include "../../core/core.h"

#include "vulkan_swap_chain.h"
#include "vulkan_pipeline_impl.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanRenderer;

    class VulkanCommandBuffer {
        public:
            VkCommandBuffer commandBuffer;

            VulkanCommandBuffer();

            VulkanCommandBuffer& begin_record();
            VulkanCommandBuffer& end_record();

            VulkanCommandBuffer& begin_render_pass(std::shared_ptr<VulkanSwapChain>& swapChain, const u32& frameBuffer);
            VulkanCommandBuffer& end_render_pass();

            VulkanCommandBuffer& set_viewport(const i32& x, const i32& y, const u32& width, const u32& height);

            VulkanCommandBuffer& bind_pipeline(VulkanPipeline& pipeline);

            VulkanCommandBuffer& bind_vertex_buffer(std::shared_ptr<VulkanBufferImpl>& buffer) {
                VkBuffer buffers[] = {buffer->get_buffer()};
                VkDeviceSize offset[] = {0};
                vkCmdBindVertexBuffers(commandBuffer, 0, 1, buffers, offset);

                return *this;
            }

            VulkanCommandBuffer& bind_index_buffer(std::shared_ptr<VulkanBufferImpl>& indexBuffer);
            VulkanCommandBuffer& bind_descriptor_set(VulkanPipelineLayoutImpl& pipelineLayout, VkDescriptorSet& descriptorSet);

            VulkanCommandBuffer& push_constant(VulkanPipelineLayoutImpl& pipelineLayout, const uint32_t& size, const void* ptr);
            VulkanCommandBuffer& push_constant(VulkanPipelineLayoutImpl& pipelineLayout, const uint32_t& size, const size_t& offset, const void* ptr);

            VulkanCommandBuffer& draw(const size_t& vertexCount);
            VulkanCommandBuffer& draw_indexed(const size_t& vertexCount);
    };
}

#endif
