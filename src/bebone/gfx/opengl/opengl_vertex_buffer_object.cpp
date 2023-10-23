#include "opengl_vertex_buffer_object.h"

namespace bebone::gfx::opengl {
    GLVertexBufferObject::GLVertexBufferObject(const void* vertices, const size_t& size, const GLenum& usage) : GLBufferObject() {
        bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
    }

    void GLVertexBufferObject::buffer_sub_data(GLintptr offset, GLsizeiptr size, const void* data) {
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
