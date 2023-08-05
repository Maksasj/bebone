#ifndef _BEBONE_GFX_RENDERING_APIS_H_
#define _BEBONE_GFX_RENDERING_APIS_H_

#include "gfx_backend.h"

namespace bebone::gfx {
    enum RenderingApis {
        NONE,
        OPENGL,
        VULKAN,
    };
}
#endif
