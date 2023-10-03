#ifndef _OPENGL_VAO_H_
#define _OPENGL_VAO_H_

#include "opengl_buffer.h"
#include "opengl_vbo.h"

namespace bebone::gfx::opengl {
    class GLVertexArrayObject : public GLBufferObject {
        public:
            GLVertexArrayObject();

            void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
            
            void bind();
            void unbind();
            void destroy();
    };
}

#endif
