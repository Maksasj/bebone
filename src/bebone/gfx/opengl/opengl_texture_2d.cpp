#include "opengl_texture_2d.h"

namespace bebone::gfx {
    void GLTexture2D::create_gl_texture() {
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

    template<typename Color>
    void GLTexture2D::create_gl_texture(const std::shared_ptr<Image<Color>>& image) {
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

    template void GLTexture2D::create_gl_texture<ColorRGB24>(const std::shared_ptr<Image<ColorRGB24>>& image);
    template void GLTexture2D::create_gl_texture<ColorRGBA32>(const std::shared_ptr<Image<ColorRGBA32>>& image);
    template void GLTexture2D::create_gl_texture<ColorRGBA32F>(const std::shared_ptr<Image<ColorRGBA32F>>& image);

    GLTexture2D::GLTexture2D(const int& width, const int& height)
            : GLTexture(GL_TEXTURE_2D),
              width(width),
              height(height)
    {
        create_gl_texture();
    }

    GLTexture2D::GLTexture2D(const std::string& file_path)
            : GLTexture(GL_TEXTURE_2D),
              width(0),
              height(0)
    {
        auto image = Image<ColorRGBA>::load_from_file(file_path);
        create_gl_texture<ColorRGBA>(image);
    }

    template<typename Color>
    GLTexture2D::GLTexture2D(const std::shared_ptr<Image<Color>>& image)
            : GLTexture(GL_TEXTURE_2D),
              width(0),
              height(0)
    {
        create_gl_texture<Color>(image);
    }

    template GLTexture2D::GLTexture2D(const std::shared_ptr<Image<ColorRGB24>>& image);
    template GLTexture2D::GLTexture2D(const std::shared_ptr<Image<ColorRGBA32>>& image);
    template GLTexture2D::GLTexture2D(const std::shared_ptr<Image<ColorRGBA32F>>& image);

    const int& GLTexture2D::get_width() const {
        return width;
    }

    const int& GLTexture2D::get_height() const {
        return height;
    }
}
