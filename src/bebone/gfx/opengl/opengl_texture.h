#ifndef _OPENGL_TEXTURE_H_
#define _OPENGL_TEXTURE_H_

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    class GLTexture : private core::NonCopyable {
        private:
            GLuint id;
            GLenum textureType;
            int width;
            int height;

        public:
            GLTexture(const char* image, GLenum textureType, GLenum format, GLenum pixelType);
            ~GLTexture();

            void bind_texture_unit(const GLuint& textureUnit);

            void bind();
            void unbind();
            void destroy();

            int get_width() const;
            int get_height() const;
    };
}

#endif
