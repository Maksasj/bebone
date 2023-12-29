#ifndef _BEBONE_GFX_OPENGL_OPENGL_ELEMENT_BUFFER_OBJECT_H_
#define _BEBONE_GFX_OPENGL_OPENGL_ELEMENT_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"

namespace bebone::gfx::opengl {
    class GLElementBufferObject final : public GLBufferObject {
        public:
            GLElementBufferObject(const void* indices, const size_t& size);
            GLElementBufferObject(const void* indices, const size_t& size, const GLenum& usage);

            ~GLElementBufferObject();

            void buffer_sub_data(GLintptr offset, GLsizeiptr size, const void* data);

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
