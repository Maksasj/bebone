#ifndef _BEBONE_GFX_SHADER_H_
#define _BEBONE_GFX_SHADER_H_

#include "gfx_backend.h"

namespace bebone::gfx {
    class IShader {
        public:
            virtual void compile() = 0;
            virtual void activate() const = 0;
            virtual void terminate() const = 0;
    };
}
#endif
