#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_CUBE_MAP_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_CUBE_MAP_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    class GLTextureCubeMap : public GLTexture {
        private:
            template<typename _Color>
            void create_cube_map_texture(const std::array<std::shared_ptr<Image<_Color>>, 6>& images) {
                bind();

                for(auto i = 0; i < 6; ++i) {
                    const auto width = images[i]->get_width();
                    const auto height = images[i]->get_height();

                    const auto format = ColorRGBA::get_gl_format();
                    const auto type = ColorRGBA::get_gl_type();

                    glTexImage2D(
                        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, format, width, height, 0,
                        format, type, images[i]->data());
                }

                const GLTextureParameters parameters;
                configure_gl_texture(parameters);
                generate_mipmap();

                unbind();
            }

        public:
            GLTextureCubeMap(const std::vector<std::string>& filePaths) : GLTexture(GL_TEXTURE_CUBE_MAP) {
                std::array<std::shared_ptr<Image<ColorRGBA>>, 6> images = {
                    Image<ColorRGBA>::load_from_file(filePaths[0]),
                    Image<ColorRGBA>::load_from_file(filePaths[1]),
                    Image<ColorRGBA>::load_from_file(filePaths[2]),
                    Image<ColorRGBA>::load_from_file(filePaths[3]),
                    Image<ColorRGBA>::load_from_file(filePaths[4]),
                    Image<ColorRGBA>::load_from_file(filePaths[5]),
                };

                create_cube_map_texture(images);
            }

            template<typename _Color>
            GLTextureCubeMap(const std::array<std::shared_ptr<Image<_Color>>, 6>& images) : GLTexture(GL_TEXTURE_CUBE_MAP) {
                create_cube_map_texture(images);
            }
    };
}

#endif
