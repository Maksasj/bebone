#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>

#include "../../core/core.h"

#include "../vertex_buffer.h"
#include "../index_buffer.h"
#include "../pipeline_layout.h"

#include "vulkan_swap_chain.h"

#include "vulkan_pipeline_impl.h"

#include "../pipeline.h"

#include "vulkan_commands.h"

namespace bebone::gfx {
    using namespace bebone::core;

    class VulkanRenderer;

    class VulkanCommandBuffer {
        private:
            core::ArenaContainer arena;

        public:
            const size_t _frameIndex;

            VkCommandBuffer commandBuffer;

            VulkanCommandBuffer(const size_t& frameIndex);

            void begin_record();
            void end_record();

            void begin_render_pass(VulkanRenderer& renderer, const u32& frameBuffer);
            void end_render_pass();

            void set_viewport(const i32& x, const i32& y, const u32& width, const u32& height);

            void bind_pipeline(Pipeline& pipeline);

            void bind_vertex_buffer(VertexBuffer& vertexBuffer) {
                VulkanBindVertexBufferCommand* ptrTarget = static_cast<VulkanBindVertexBufferCommand*>(arena.alloc(sizeof(VulkanBindVertexBufferCommand)));
                std::ignore = new (ptrTarget) VulkanBindVertexBufferCommand(commandBuffer, *static_cast<VulkanVertexBufferImpl*>(vertexBuffer.get_impl()));
            }

            void bind_index_buffer(IndexBuffer& indexBuffer);
            void bind_descriptor_set(PipelineLayout& pipelineLayout, VkDescriptorSet& descriptorSet);

            void push_constant(PipelineLayout& pipelineLayout, const uint32_t& size, const void* ptr);
            void push_constant(PipelineLayout& pipelineLayout, const uint32_t& size, const size_t& offset, const void* ptr);

            void draw(const size_t& vertexCount);
            void draw_indexed(const size_t& vertexCount);

            void preprocess();
            void submit();
    };
}

#endif
