#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_2D_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_2D_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    class GLTexture2D : public GLTexture {
        private:
            int width;
            int height;

            void create_gl_texture();

            template<typename _Color>
            void create_gl_texture(const std::shared_ptr<Image<_Color>>& image);

        public:
            /*!
            * Constructor
            * @param width - Texture width
            * @param height - Texture height
            */
            GLTexture2D(const int& width, const int& height);

            /*!
            * Constructor, loads image from a file
            * @param filePath - Image file path
            */
            GLTexture2D(const std::string& filePath);

            /*!
            * Constructor, creates GLTexture2D from already loaded image
            * @param image - Image
            */
            template<typename _Color>
            GLTexture2D(const std::shared_ptr<Image<_Color>>& image);

            // Getter for image width
            const int& get_width() const;

            // Getter for image height
            const int& get_height() const;
    };
}

#endif
