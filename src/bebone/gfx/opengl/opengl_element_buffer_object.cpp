#include "opengl_element_buffer_object.h"

namespace bebone::gfx::opengl {
    GLElementBufferObject::GLElementBufferObject(const std::vector<GLuint>& indices, const GLenum& usage) : GLBufferObject() {
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), usage);
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
