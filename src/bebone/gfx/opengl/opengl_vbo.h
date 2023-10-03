#ifndef _OPENGL_VBO_H_
#define _OPENGL_VBO_H_

#include "opengl_buffer.h"

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
