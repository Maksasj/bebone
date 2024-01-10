#ifndef _BEBONE_GFX_OPENGL_OPENGL_GPU_PROPERTIES_H_
#define _BEBONE_GFX_OPENGL_OPENGL_GPU_PROPERTIES_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLGpuProperties : private core::NonCopyable {
        public:
            static int texture_unit_capacity();
    };
}

#endif
