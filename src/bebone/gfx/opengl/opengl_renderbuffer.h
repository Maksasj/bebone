#ifndef _BEBONE_GFX_OPENGL_OPENGL_RENDERBUFFER_H_
#define _BEBONE_GFX_OPENGL_OPENGL_RENDERBUFFER_H_

#include "../gfx_backend.h"
#include "../shaders/shader_code.h"

#include "opengl_shader_properties.h"
#include "opengl_uniform_buffer_object.h"

#include "opengl_texture_2d.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLRenderbuffer : private core::NonCopyable {
        private:
            GLuint id;

        public:
            GLRenderbuffer();

            // Todo
            void storage(const u32& type, const u32& width, const u32& height);

            void bind();
            void unbind();

            GLuint get_id() const;
    };
}

#endif
