#ifndef _BEBONE_GFX_RENDERER_H_
#define _BEBONE_GFX_RENDERER_H_

#include <memory>

#include "gfx_backend.h"

#include "command_buffer.h"
#include "command_buffer_pool.h"

namespace bebone::gfx {
    class Renderer {
        private:

        public:
            virtual ~Renderer() {}

            virtual CommandBuffer& get_command_buffer() = 0;
            virtual CommandBufferPool& get_command_buffer_pool() = 0;
    };
}
#endif
