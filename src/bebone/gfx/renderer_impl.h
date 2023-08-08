#ifndef _BEBONE_GFX_RENDERER_IMPLEMENTATION_H_
#define _BEBONE_GFX_RENDERER_IMPLEMENTATION_H_

#include <memory>

#include "gfx_backend.h"

#include "vertex_buffer_impl.h"
#include "command_buffer.h"
#include "command_buffer_pool.h"

namespace bebone::gfx {
    class RendererImpl {
        private:

        public:
            virtual ~RendererImpl() {}

            virtual CommandBuffer& get_command_buffer() = 0;
            virtual CommandBufferPool& get_command_buffer_pool() = 0;

            virtual Pipeline create_pipeline(const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) = 0;
            virtual VertexBuffer create_vertex_buffer(const std::vector<Vertex>&) = 0;
            virtual std::shared_ptr<MyEngineSwapChainImpl> get_swap_chain() = 0;

            virtual void present() = 0;
    };
}
#endif
