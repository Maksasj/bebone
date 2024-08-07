#include "opengl_gpu_properties.h"

namespace bebone::gfx {
    int GLGpuProperties::texture_unit_capacity() {
        int texture_unit_capacity = 0;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texture_unit_capacity);

        return texture_unit_capacity;
    }
}