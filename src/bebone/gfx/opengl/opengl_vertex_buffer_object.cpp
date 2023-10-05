#include "opengl_vertex_buffer_object.h"

namespace bebone::gfx::opengl {

    GLVertexBufferObject::GLVertexBufferObject(const std::vector<GLfloat>& vertices) : GLBufferObject() {
	    glBindBuffer(GL_ARRAY_BUFFER, id);
	    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
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
