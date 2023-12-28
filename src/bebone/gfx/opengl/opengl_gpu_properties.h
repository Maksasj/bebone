#ifndef _OPENGL_GPU_PROPERTIES_H_
#define _OPENGL_GPU_PROPERTIES_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLGpuProperties : private core::NonCopyable {
        public:
            static int texture_unit_capacity();
    };
}

#endif
