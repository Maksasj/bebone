#ifndef _BEBONE_GFX_COMMAND_BUFFER_H_
#define _BEBONE_GFX_COMMAND_BUFFER_H_

#include "../core/arena_allocator.h"

#include "swap_chain_impl.h"
#include "rendering_api.h"

#include "pipeline_layout.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "uniform_buffer.h"

#include "pipeline.h"

#include "gfx_backend.h"

namespace bebone::gfx {
    class CommandBuffer {
        private:

        public:
            virtual ~CommandBuffer() {}

            virtual void begin_record() = 0;
            virtual void end_record() = 0;

            virtual void begin_render_pass(MyEngineSwapChainImpl& swapChain, int frameBuffer) = 0;
            virtual void end_render_pass() = 0;

            virtual void bind_pipeline(Pipeline& pipeline) = 0;
            
            virtual void bind_vertex_buffer(VertexBuffer& vertexBuffer) = 0;
            virtual void bind_index_buffer(IndexBuffer& indexBuffer) = 0;
            // virtual void bind_descriptor_set(PipelineLayout& pipelineLayout, VkDescriptorSet& descriptorSet) = 0;
            virtual void bind_uniform_buffer(PipelineLayout& pipelineLayout, UniformBuffer& uniformBuffer) = 0;

            virtual void draw(const size_t& vertexCount) = 0;
            virtual void draw_indexed(const size_t& vertexCount) = 0;

            virtual void submit() = 0;
            virtual void preprocess() = 0;

            virtual RenderingApi get_api() = 0;
    };
}

#endif
