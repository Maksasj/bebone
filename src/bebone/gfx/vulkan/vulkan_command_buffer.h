#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>

#include "../../core/arena_container.h"

#include "../vertex_buffer.h"
#include "../index_buffer.h"
#include "../pipeline_layout.h"

#include "../swap_chain_impl.h"

#include "vulkan_pipeline_impl.h"

namespace bebone::gfx {
    class VulkanRenderer;

    class VulkanCommandBuffer {
        private:
            core::ArenaContainer arena;

        public:
            const size_t _frameIndex;

            VulkanCommandBuffer(const size_t& frameIndex);

            void begin_record();
            void end_record();

            void begin_render_pass(VulkanRenderer& renderer, int frameBuffer);
            void end_render_pass();

            void bind_pipeline(VulkanPipeline& pipeline);
            
            void bind_vertex_buffer(VertexBuffer& vertexBuffer);
            void bind_index_buffer(IndexBuffer& indexBuffer);
            void bind_descriptor_set(PipelineLayout& pipelineLayout, VkDescriptorSet& descriptorSet);

            // void bind_uniform_buffer(PipelineLayout& pipelineLayout, UniformBuffer& uniformBuffer);
            void push_constant(PipelineLayout& pipelineLayout, const uint32_t& size, const void* ptr);

            void draw(const size_t& vertexCount);
            void draw_indexed(const size_t& vertexCount);

            void preprocess();
            void submit();

            VkCommandBuffer commandBuffer;
    };  
}

#endif
