#ifndef _OPENGL_UNIFORM_BUFFER_OBJECT_H_
#define _OPENGL_UNIFORM_BUFFER_OBJECT_H_

#include "opengl_buffer_object.h"
#include <vector>

namespace bebone::gfx::opengl {
    using namespace bebone::core;

    class GLUniformBufferObject final : public GLBufferObject {
        private:
            u64 size;

        public:
            GLUniformBufferObject(const u64& _size);

            // Todo lets write destructor

            void bind_buffer_base(const i32& binding) const;

            void* map() const;
            void unmap() const;

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
