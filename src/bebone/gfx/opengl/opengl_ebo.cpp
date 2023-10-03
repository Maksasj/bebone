#include "opengl_ebo.h"

namespace bebone::gfx::opengl {
    GLElementBufferObject::GLElementBufferObject(GLuint* indices, GLsizeiptr size) {
        glGenBuffers(1, &id);
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }

    void GLElementBufferObject::bind() {
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    }

    void GLElementBufferObject::unbind() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void GLElementBufferObject::destroy() {
        glDeleteBuffers(1, &id);
    }
}
