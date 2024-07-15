#ifndef _BEBONE_RENDERER_ITEXTURE_H_
#define _BEBONE_RENDERER_ITEXTURE_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    class ITexture {
        public:
            virtual ~ITexture() = default;
    };
}

#endif
