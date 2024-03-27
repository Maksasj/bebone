#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    GLTexture::GLTexture(const std::string& filePath, const GLenum& textureType)
        : textureType(textureType)
    {
        auto image = Image<ColorRGBA>::load_from_file(filePath);

        width = image->get_width();
        height = image->get_height();

        create_gl_texture(image->data(), ColorRGBA::get_gl_format(), ColorRGBA::get_gl_type());
    }

    GLTexture::~GLTexture() {
        destroy();
    }

    void GLTexture::create_gl_texture(void* data, const GLenum& format, const GLenum& pixelType) {
        glGenTextures(1, &id);
        glBindTexture(textureType, id);

        glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_NEAREST);
        glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_NEAREST);

        glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelType, data);
        glGenerateMipmap(textureType);

        glBindTexture(textureType, 0);
    }

    void GLTexture::bind_texture_unit(const GLuint& textureUnit) {
        glBindTextureUnit(textureUnit, id);
    }

    void GLTexture::bind() {
        glBindTexture(textureType, id);
    }

    void GLTexture::unbind() {
        glBindTexture(textureType, 0);
    }

    void GLTexture::destroy() {
        glDeleteTextures(1, &id);
    }

    const int& GLTexture::get_width() const {
        return width;
    }

    const int& GLTexture::get_height() const {
        return height;
    }
}
