#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_H_

#include "../../assets/image/image.tpp"

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

            template<typename _Color>
            GLTexture(const std::shared_ptr<Image<_Color>>& image, const GLenum& textureType, const GLenum& format, const GLenum& pixelType)
                : textureType(textureType), width(image->get_width()), height(image->get_height()) {

                glGenTextures(1, &id);
                glBindTexture(textureType, id);

                glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

                glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_NEAREST);
                glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_NEAREST);

                glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelType, image->data());
                glGenerateMipmap(textureType);

                glBindTexture(textureType, 0);
            }

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
