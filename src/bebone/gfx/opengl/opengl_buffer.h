#ifndef _OPENGL_BUFFER_H_
#define _OPENGL_BUFFER_H_

#include <glad/glad.h>

namespace bebone::gfx::opengl {
    class Buffer {
        private:
            GLuint id;

        public:
            GLuint getID();
            virtual void bind() = 0;
            virtual void unbind() = 0;
            virtual void destroy() = 0;
    };
}

#endif
