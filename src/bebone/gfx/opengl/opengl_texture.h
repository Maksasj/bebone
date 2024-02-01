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

            void create_gl_texture(void* data, const GLenum& format, const GLenum& pixelType);

        public:
            /*!
             * Loads image from file and creates opengl texture
             * @param image - path to the image file
             * @param textureType - specifies the texture (1D/2D/3D)
            */
            GLTexture(const std::string& filePath, const GLenum& textureType);

            template<typename _Color>
            GLTexture(const std::shared_ptr<Image<_Color>>& image, const GLenum& textureType)
                : textureType(textureType), width(image->get_width()), height(image->get_height()) {

                create_gl_texture(image->data(), _Color::get_gl_format(), _Color::get_gl_type());
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
            const int& get_width() const;

            /// Get texture height in pixels
            const int& get_height() const;
    };
}

#endif
