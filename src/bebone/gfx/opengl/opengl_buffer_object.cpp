#include "opengl_buffer_object.h"

namespace bebone::gfx::opengl {
    GLBufferObject::GLBufferObject() {
        glGenBuffers(1, &id);
    }
}