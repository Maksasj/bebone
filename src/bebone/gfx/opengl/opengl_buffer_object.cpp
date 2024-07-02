#include "opengl_buffer_object.h"

namespace bebone::gfx {
    GLBufferObject::GLBufferObject() {
        glGenBuffers(1, &id);
    }
}