#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    GLTexture::GLTexture(const GLenum& texture_type) : texture_type(texture_type) {
        glGenTextures(1, &id);
    }

    GLTexture::~GLTexture() {
        destroy();
    }

    void GLTexture::configure_gl_texture(const GLTextureParameters& parameters) {
        for(auto& param : parameters.parameters)
            glTexParameteri(texture_type, param.first, param.second);
    };

    void GLTexture::generate_mipmap() {
        glGenerateMipmap(texture_type);
    }

    const GLuint& GLTexture::get_id() const {
        return id;
    }

    const GLenum& GLTexture::get_texture_type() const {
        return texture_type;
    }

    void GLTexture::bind_texture_unit(const GLuint& texture_unit) {
        glBindTextureUnit(texture_unit, id);
    }

    void GLTexture::bind() {
        glBindTexture(texture_type, id);
    }

    void GLTexture::unbind() {
        glBindTexture(texture_type, 0);
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
