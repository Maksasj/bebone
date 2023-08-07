#ifndef _BEBONE_GFX_RENDERER_H_
#define _BEBONE_GFX_RENDERER_H_

#include <memory>

#include "gfx_backend.h"

#include "vertex_buffer.h"
#include "command_buffer.h"
#include "command_buffer_pool.h"

namespace bebone::gfx {
    class Renderer {
        private:

        public:
            virtual ~Renderer() {}

            virtual CommandBuffer& get_command_buffer() = 0;
            virtual CommandBufferPool& get_command_buffer_pool() = 0;

            virtual std::shared_ptr<Pipeline> create_pipeline(const std::vector<unsigned int>& vertexSpirvCode, const std::vector<unsigned int>& fragmentSpirvCode) = 0;
            virtual std::shared_ptr<VertexBuffer> create_vertex_buffer(const std::vector<Vertex>&) = 0;
            virtual std::shared_ptr<MyEngineSwapChain> get_swap_chain() = 0;

            virtual void present() = 0;
    };
}
#endif
