#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    class GLTexture : private core::NonCopyable {
        private:
            GLuint id;
            GLenum textureType;
            int width;
            int height;

        public:
            /*!
             * Creates texture using stb library
             * @param image - path to the image file
             * @param textureType - specifies the texture (1D/2D/3D)
             * @param format - specifies the RGB format
             * @param pixelType - specifies the data type
             */
            GLTexture(const char* image, const GLenum& textureType, const GLenum& format, const GLenum& pixelType);
            GLTexture(const std::shared_ptr<Image>& image, const GLenum& textureType, const GLenum& format, const GLenum& pixelType);

            ~GLTexture();

            /*!
             * Binds texture to the specified texture unit
             * @param textureUnit - texture unit, to which texture should be bound to
             */
            void bind_texture_unit(const GLuint& textureUnit);

            /// Binds texture
            void bind();

            /// Unbinds texture
            void unbind();

            /// Destroys texture. Calls automatically in the destructor
            void destroy();

            /// Get texture width in pixels
            int get_width() const;

            /// Get texture height in pixels
            int get_height() const;
    };
}

#endif
