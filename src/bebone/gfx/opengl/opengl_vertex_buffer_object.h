#ifndef _OPENGL_VERTEX_BUFFER_OBJECT_H_
#define _OPENGL_VERTEX_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"

namespace bebone::gfx::opengl {
    class GLVertexBufferObject : public GLBufferObject {
        public:
            GLVertexBufferObject(GLfloat* vertices, GLsizeiptr size);
            void bind();
            void unbind();
            void destroy();
    };
}

#endif
