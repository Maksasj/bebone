#include "opengl_vbo.h"

namespace bebone::gfx::opengl {
    GLVertexBufferObject::GLVertexBufferObject(GLfloat* vertices, GLsizeiptr size) {
        glGenBuffers(1, &id);
	    glBindBuffer(GL_ARRAY_BUFFER, id);
	    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
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
