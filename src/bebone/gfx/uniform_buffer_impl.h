#ifndef _BEBONE_GFX_UNIFORM_BUFFER_IMPLEMENTATION_H_
#define _BEBONE_GFX_UNIFORM_BUFFER_IMPLEMENTATION_H_

#include "buffer_impl.h"

namespace bebone::gfx {
    class UniformBufferImpl {
        public:
            virtual void* data() = 0;
    };
}

#endif
