#include "opengl_renderbuffer.h"

namespace bebone::gfx::opengl {
    GLRenderbuffer::GLRenderbuffer() {
        glGenRenderbuffers(1, &id);
    }

    void GLRenderbuffer::storage(const u32& type, const u32& width, const u32& height) {
        glRenderbufferStorage(GL_RENDERBUFFER, type, width, height);
    }

    void GLRenderbuffer::bind() {
        glBindRenderbuffer(GL_RENDERBUFFER, id);
    }

    void GLRenderbuffer::unbind() {
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
    }

    GLuint GLRenderbuffer::get_id() const {
        return id;
    }
}
