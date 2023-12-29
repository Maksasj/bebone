#ifndef _BEBONE_GFX_OPENGL_OPENGL_BUFFER_OBJECT_H_
#define _BEBONE_GFX_OPENGL_OPENGL_BUFFER_OBJECT_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLBufferObject : private core::NonCopyable {
        protected:
            GLuint id;

        public:
            GLBufferObject();

            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void destroy() = 0;
    };
}

#endif
