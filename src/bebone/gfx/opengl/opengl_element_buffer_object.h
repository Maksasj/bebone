#ifndef _OPENGL_ELEMENT_BUFFER_OBJECT_H_
#define _OPENGL_ELEMENT_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"

namespace bebone::gfx::opengl {
    class GLElementBufferObject final : public GLBufferObject {
        public:
            GLElementBufferObject(const GLuint* indices, const size_t& size);
            GLElementBufferObject(const GLuint* indices, const size_t& size, const GLenum& usage);

            void buffer_sub_data(GLintptr offset, GLsizeiptr size, const void* data);

            // Todo lets write destructor

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
