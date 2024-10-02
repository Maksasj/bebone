#include "opengl_texture_cube_map.h"

namespace bebone::gfx {
    template<typename Color>
    void GLTextureCubeMap::create_cube_map_texture(const std::array<std::shared_ptr<Image<Color>>, 6>& images) {
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

    template void GLTextureCubeMap::create_cube_map_texture<ColorRGB24>(const std::array<std::shared_ptr<Image<ColorRGB24>>, 6>& images);
    template void GLTextureCubeMap::create_cube_map_texture<ColorRGBA32>(const std::array<std::shared_ptr<Image<ColorRGBA32>>, 6>& images);
    template void GLTextureCubeMap::create_cube_map_texture<ColorRGBA32F>(const std::array<std::shared_ptr<Image<ColorRGBA32F>>, 6>& images);

    GLTextureCubeMap::GLTextureCubeMap(const std::vector<std::string>& file_paths) : GLTexture(GL_TEXTURE_CUBE_MAP) {
        std::array<std::shared_ptr<Image<ColorRGBA>>, 6> images = {
            Image<ColorRGBA>::load_from_file(file_paths[0], false), // Todo
            Image<ColorRGBA>::load_from_file(file_paths[1], false),
            Image<ColorRGBA>::load_from_file(file_paths[2], false),
            Image<ColorRGBA>::load_from_file(file_paths[3], false),
            Image<ColorRGBA>::load_from_file(file_paths[4], false),
            Image<ColorRGBA>::load_from_file(file_paths[5], false)
        };

        create_cube_map_texture(images);
    }

    template<typename Color>
    GLTextureCubeMap::GLTextureCubeMap(const std::array<std::shared_ptr<Image<Color>>, 6>& images) : GLTexture(GL_TEXTURE_CUBE_MAP) {
        create_cube_map_texture<Color>(images);
    }

    template GLTextureCubeMap::GLTextureCubeMap(const std::array<std::shared_ptr<Image<ColorRGB24>>, 6>& images);
    template GLTextureCubeMap::GLTextureCubeMap(const std::array<std::shared_ptr<Image<ColorRGBA32>>, 6>& images);
    template GLTextureCubeMap::GLTextureCubeMap(const std::array<std::shared_ptr<Image<ColorRGBA32F>>, 6>& images);
}
