#ifndef _OPENGL_VERTEX_BUFFER_OBJECT_H_
#define _OPENGL_VERTEX_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    class GLVertexBufferObject : public GLBufferObject {
        public:
            GLVertexBufferObject(const std::vector<GLfloat>& vertices);

            GLVertexBufferObject(const GLVertexBufferObject &) = delete;
            void operator=(const GLVertexBufferObject &) = delete;
            GLVertexBufferObject(GLVertexBufferObject &&) = delete;
            GLVertexBufferObject &operator=(GLVertexBufferObject &&) = delete;

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
