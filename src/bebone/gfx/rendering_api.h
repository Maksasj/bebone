#ifndef _BEBONE_GFX_RENDERING_API_H_
#define _BEBONE_GFX_RENDERING_API_H_

#include "gfx_backend.h"

namespace bebone::gfx {
    enum RenderingApi {
        NONE,
        OPENGL,
        VULKAN,
    };
}

#endif
