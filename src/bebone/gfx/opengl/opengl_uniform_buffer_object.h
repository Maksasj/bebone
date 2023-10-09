#ifndef _OPENGL_UNIFORM_BUFFER_OBJECT_H_
#define _OPENGL_UNIFORM_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLUniformBufferObject : public GLBufferObject {
        private:
            i64 size;

        public:
            GLUniformBufferObject(const i64& _size);

            void bind_buffer_base(const i32& binding) const;

            void* map() const;
            void unmap() const;

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
