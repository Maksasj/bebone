#include "opengl_uniform_buffer_object.h"

namespace bebone::gfx::opengl {
    GLUniformBufferObject::GLUniformBufferObject(const u64& _size) : GLBufferObject(), size(_size) {
        bind();

        glBufferData(GL_UNIFORM_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    }

    GLUniformBufferObject::~GLUniformBufferObject() {
        destroy();
    }

    void GLUniformBufferObject::bind_buffer_base(const i32& binding) const {
        glBindBufferBase(GL_UNIFORM_BUFFER, binding, id);
    }

    void* GLUniformBufferObject::map() const {
        return glMapBufferRange(GL_UNIFORM_BUFFER, 0, size, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    }

    void GLUniformBufferObject::unmap() const {
        glUnmapBuffer(GL_UNIFORM_BUFFER);
    }

    void GLUniformBufferObject::bind() {
        glBindBuffer(GL_UNIFORM_BUFFER, id);
    }

    void GLUniformBufferObject::unbind() {
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }

    void GLUniformBufferObject::destroy() {
        glDeleteBuffers(1, &id);
    }
}
