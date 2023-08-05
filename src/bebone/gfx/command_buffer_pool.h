#ifndef _BEBONE_GFX_COMMAND_BUFFER_POOL_H_
#define _BEBONE_GFX_COMMAND_BUFFER_POOL_H_

#include "../core/arena_allocator.h"

#include "gfx_backend.h"

namespace bebone::gfx {
    class CommandBufferPool {
        private:

        public:
            virtual CommandBuffer& get_command_buffer(const size_t& commandBufferIndex) = 0;
    };
}

#endif
