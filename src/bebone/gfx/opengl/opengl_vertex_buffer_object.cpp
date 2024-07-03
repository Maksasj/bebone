#include "opengl_vertex_buffer_object.h"

namespace bebone::gfx {
    GLVertexBufferObject::GLVertexBufferObject(const void* vertices, const GLsizeiptr& size, const GLenum& usage) : GLBufferObject() {
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    }

    GLVertexBufferObject::~GLVertexBufferObject() {
        destroy();
    }

    void GLVertexBufferObject::buffer_sub_data(const GLintptr& offset, const GLsizeiptr& size, const void* data) {
        bind();
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
        unbind();
    }
    
    void GLVertexBufferObject::bind() {
        glBindBuffer(GL_ARRAY_BUFFER, id);
    }

    void GLVertexBufferObject::unbind() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void GLVertexBufferObject::destroy() {
        glDeleteBuffers(1, &id);
    }
}
