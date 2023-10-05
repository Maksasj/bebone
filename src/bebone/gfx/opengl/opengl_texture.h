#ifndef _OPENGL_TEXTURE_H_
#define _OPENGL_TEXTURE_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLTexture {
        private:
            GLuint id;

        public:
            GLTexture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

            GLTexture(const GLTexture &) = delete;
            void operator=(const GLTexture &) = delete;
            GLTexture(GLTexture &&) = delete;
            GLTexture &operator=(GLTexture &&) = delete;

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
