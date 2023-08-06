#ifndef _BEBONE_GFX_COMMAND_BUFFER_H_
#define _BEBONE_GFX_COMMAND_BUFFER_H_

#include "../core/arena_allocator.h"

#include "rendering_apis.h"

#include "gfx_backend.h"

namespace bebone::gfx {
    class CommandBuffer {
        private:

        public:
            virtual ~CommandBuffer() {}

            virtual void begin_record() = 0;
            virtual void end_record() = 0;

            virtual void* push_bytes(const size_t&) = 0;

            virtual void preprocess() = 0;

            virtual RenderingApi get_api() = 0;
    };
}

#endif
