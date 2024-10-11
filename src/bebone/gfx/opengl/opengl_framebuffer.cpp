#include "opengl_framebuffer.h"

namespace bebone::gfx {
    using namespace bebone::core;

    GLFramebuffer::GLFramebuffer() {
        glGenFramebuffers(1, &id);
    }

    void GLFramebuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void GLFramebuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void GLFramebuffer::attach_texture_2d(const u32& attachment, GLTexture2D& texture) {
        bind();

        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, texture.get_id(), 0);

        unbind();
    }

    void GLFramebuffer::attach_renderbuffer(const u32& attachment, GLRenderbuffer& renderbuffer) {
        bind();

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, renderbuffer.get_id());

        unbind();
    }
}
