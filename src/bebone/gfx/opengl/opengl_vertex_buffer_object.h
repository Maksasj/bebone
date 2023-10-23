#ifndef _OPENGL_VERTEX_BUFFER_OBJECT_H_
#define _OPENGL_VERTEX_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    class GLVertexBufferObject final : public GLBufferObject {
        public:
            GLVertexBufferObject(const void* vertices, const size_t& size, const GLenum& usage);

            void buffer_sub_data(GLintptr offset, GLsizeiptr size, const void* data);

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
