#include "opengl_vertex_array_object.h"

namespace bebone::gfx::opengl {
    GLVertexArrayObject::GLVertexArrayObject() {
        glGenVertexArrays(1, &id);
    }

    void GLVertexArrayObject::link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, const u64& offset) {
        vbo.bind();

        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, (void*)(offset));
        glEnableVertexAttribArray(layout);

        vbo.unbind();
    }

    void GLVertexArrayObject::link_attributes(GLVertexBufferObject& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
        vbo.bind();

        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);

        vbo.unbind();
    }

    void GLVertexArrayObject::bind() {
        glBindVertexArray(id);
    }

    void GLVertexArrayObject::unbind() {
        glBindVertexArray(0);
    }

    void GLVertexArrayObject::destroy() {
        glDeleteVertexArrays(1, &id);
    }
}
