#ifndef _BEBONE_GFX_BUFFER_OBJECT_H_
#define _BEBONE_GFX_BUFFER_OBJECT_H_

#include "gfx_backend.h"

namespace bebone::gfx {
    class IBufferObject {
        public:
            virtual void bind() const = 0;
            virtual void unbind() const = 0;
            virtual void terminate() const = 0;
    };
}
#endif
