#ifndef _BEBONE_GFX_RENDERER_H_
#define _BEBONE_GFX_RENDERER_H_

#include <memory>

#include "gfx_backend.h"

#include "command_buffer.h"

namespace bebone::gfx {
    class Renderer {
        private:

        public:
            virtual CommandBuffer& get_command_buffer() = 0;
    };
}
#endif
