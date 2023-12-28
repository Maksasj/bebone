#include "opengl_gpu_properties.h"

namespace bebone::gfx::opengl {
    int GLGpuProperties::texture_unit_capacity() {
        int textureUnitCapacity = 0;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &textureUnitCapacity);

        return textureUnitCapacity;
    }
}