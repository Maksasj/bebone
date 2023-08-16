#ifndef _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_
#define _BEBONE_GFX_VULKAN_VULKAN_COMMAND_BUFFER_H_

#include <stdexcept>

#include "../command_buffer.h"
#include "../../core/arena_container.h"

namespace bebone::gfx {
    class VulkanCommandBuffer : public CommandBuffer {
        private:
            core::ArenaContainer arena;
            const size_t _frameIndex;

        protected:

        public:
            VulkanCommandBuffer(const size_t& frameIndex);

            void begin_record() override;
            void end_record() override;

            void begin_render_pass(MyEngineSwapChainImpl& swapChain, int frameBuffer) override;
            void end_render_pass() override;

            void bind_pipeline(Pipeline& pipeline) override;
            
            void bind_vertex_buffer(VertexBuffer& vertexBuffer) override;
            void bind_index_buffer(IndexBuffer& indexBuffer) override;
            // void bind_descriptor_set(PipelineLayout& pipelineLayout, VkDescriptorSet& descriptorSet) override;

            void bind_uniform_buffer(PipelineLayout& pipelineLayout, UniformBuffer& uniformBuffer) override;

            void draw(const size_t& vertexCount) override;
            void draw_indexed(const size_t& vertexCount) override;

            void preprocess() override;
            void submit() override;

            VkCommandBuffer commandBuffer;

            RenderingApi get_api() override;
    };  
}

#endif
