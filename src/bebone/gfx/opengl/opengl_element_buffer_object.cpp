#include "opengl_element_buffer_object.h"

namespace bebone::gfx::opengl {
    GLElementBufferObject::GLElementBufferObject(const std::vector<GLuint>& indices) : GLBufferObject() {
	    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), indices.data(), GL_STATIC_DRAW);
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
