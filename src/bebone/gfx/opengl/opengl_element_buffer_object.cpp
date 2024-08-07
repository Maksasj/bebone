#include "opengl_element_buffer_object.h"

namespace bebone::gfx {
    GLElementBufferObject::GLElementBufferObject(const void* indices, const GLsizeiptr& size, const GLenum& usage) : GLBufferObject() {
        bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
    }

    GLElementBufferObject::~GLElementBufferObject() {
        destroy();
    }

    void GLElementBufferObject::buffer_sub_data(const GLintptr& offset, const GLsizeiptr& size, const void* data) {
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
