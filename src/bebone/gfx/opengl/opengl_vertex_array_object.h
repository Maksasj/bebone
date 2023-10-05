#ifndef _OPENGL_VERTEX_ARRAY_OBJECT_H_
#define _OPENGL_VERTEX_ARRAY_OBJECT_H_

#include "opengl_buffer_object.h"
#include "opengl_vertex_buffer_object.h"

namespace bebone::gfx::opengl {
    class GLVertexArrayObject : public GLBufferObject {
        public:
            GLVertexArrayObject();

            GLVertexArrayObject(const GLVertexArrayObject &) = delete;
            void operator=(const GLVertexArrayObject &) = delete;
            GLVertexArrayObject(GLVertexArrayObject &&) = delete;
            GLVertexArrayObject &operator=(GLVertexArrayObject &&) = delete;

            void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
            
            void bind();
            void unbind();
            void destroy();
    };
}

#endif
