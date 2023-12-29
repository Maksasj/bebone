#ifndef _BEBONE_GFX_OPENGL_OPENGL_VERTEX_ARRAY_OBJECT_H_
#define _BEBONE_GFX_OPENGL_OPENGL_VERTEX_ARRAY_OBJECT_H_

#include "opengl_buffer_object.h"
#include "opengl_vertex_buffer_object.h"

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLVertexArrayObject final : public GLBufferObject {
        public:
            GLVertexArrayObject();
            ~GLVertexArrayObject();

            void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const u64& offset);
            void link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
