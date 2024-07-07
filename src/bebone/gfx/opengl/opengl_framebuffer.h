#ifndef _BEBONE_GFX_OPENGL_OPENGL_FRAMEBUFFER_H_
#define _BEBONE_GFX_OPENGL_OPENGL_FRAMEBUFFER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

#include "opengl_shader_properties.h"
#include "opengl_uniform_buffer_object.h"

#include "opengl_texture_2d.h"
#include "opengl_renderbuffer.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLFramebuffer : private core::NonCopyable {
        private:
            GLuint id;

        public:
            GLFramebuffer();

            void bind();
            void unbind();

            void attach_texture_2d(const u32& attachment, GLTexture2D& texture);
            void attach_renderbuffer(const u32& attachment, GLRenderbuffer& renderbuffer);
    };
}

#endif
