#ifndef _OPENGL_BUFFER_OBJECT_H_
#define _OPENGL_BUFFER_OBJECT_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLBufferObject {
        protected:
            GLuint id;

        public:
            GLBufferObject();

            GLBufferObject(const GLBufferObject &) = delete;
            void operator=(const GLBufferObject &) = delete;
            GLBufferObject(GLBufferObject &&) = delete;
            GLBufferObject &operator=(GLBufferObject &&) = delete;

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void destroy() = 0;
    };
}

#endif
