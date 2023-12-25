#include "opengl_element_buffer_object.h"

namespace bebone::gfx::opengl {
    GLElementBufferObject::GLElementBufferObject(const GLuint* indices, const size_t& size) {
        bind();
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), indices, GL_STATIC_DRAW);
    }

    GLElementBufferObject::~GLElementBufferObject() {
        destroy();
    }
    
    GLElementBufferObject::GLElementBufferObject(const GLuint* indices, const size_t& size, const GLenum& usage) : GLBufferObject() {
        bind();
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(GLuint), indices, usage);
    }

    void GLElementBufferObject::buffer_sub_data(GLintptr offset, GLsizeiptr size, const void* data) {
        bind();
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offset, size, data);
        unbind();
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
