#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    GLTexture::GLTexture(const GLenum& textureType) : textureType(textureType) {
        glGenTextures(1, &id);
    }

    GLTexture::~GLTexture() {
        destroy();
    }

    void GLTexture::configure_gl_texture(const GLTextureParameters& parameters) {
        for(auto& param : parameters.parameters)
            glTexParameteri(textureType, param.first, param.second);
    };

    void GLTexture::generate_mipmap() {
        glGenerateMipmap(textureType);
    }

    const GLuint& GLTexture::get_id() const {
        return id;
    }

    const GLenum& GLTexture::get_texture_type() const {
        return textureType;
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

    /*
    const int& GLTexture::get_width() const {
        return width;
    }

    const int& GLTexture::get_height() const {
        return height;
    }
    */
}
