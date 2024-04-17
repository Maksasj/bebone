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

            void create_gl_texture() {
                const auto format = ColorRGBA::get_gl_format();
                const auto type = ColorRGBA::get_gl_type();

                bind();
                glTexImage2D(
                        get_texture_type(),
                        0, format, width, height, 0,
                        format, type, nullptr);

                const GLTextureParameters parameters;
                configure_gl_texture(parameters);
                generate_mipmap();
                unbind();
            }

            template<typename _Color>
            void create_gl_texture(const std::shared_ptr<Image<_Color>>& image) {
                width = image->get_width();
                height = image->get_height();

                const auto format = ColorRGBA::get_gl_format();
                const auto type = ColorRGBA::get_gl_type();

                bind();
                    glTexImage2D(
                        get_texture_type(),
                        0, format, width, height, 0,
                        format, type, image->data());

                    const GLTextureParameters parameters;
                    configure_gl_texture(parameters);
                    generate_mipmap();
                unbind();
            }

        public:
            GLTexture2D(const int& width, const int& height)
                    : GLTexture(GL_TEXTURE_2D),
                      width(width),
                      height(height)
            {
                create_gl_texture();
            }

            GLTexture2D(const std::string& filePath)
                : GLTexture(GL_TEXTURE_2D),
                  width(0),
                  height(0)
            {
                auto image = Image<ColorRGBA>::load_from_file(filePath);
                create_gl_texture<ColorRGBA>(image);
            }

            template<typename _Color>
            GLTexture2D(const std::shared_ptr<Image<_Color>>& image)
                : GLTexture(GL_TEXTURE_2D),
                  width(0),
                  height(0)
            {
                create_gl_texture<ColorRGBA>(image);
            }

            const int& get_width() const;
            const int& get_height() const;
    };
}

#endif
