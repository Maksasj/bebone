#ifndef _OPENGL_TEXTURE_H_
#define _OPENGL_TEXTURE_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLTexture : private core::NonCopyable {
        private:
            GLuint id;
            GLenum textureType;

        public:
            GLTexture(const char* image, GLenum textureType, GLenum format, GLenum pixelType);

            void bind_texture_unit(const GLuint& textureUnit);

            void bind();
            void unbind();
            void destroy();
    };
}

#endif
