#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    GLTexture::GLTexture(const char* image, GLenum textureType, GLenum format, GLenum pixelType) : textureType(textureType) {
        int colorChannelNumber;

        stbi_set_flip_vertically_on_load(true);

        unsigned char* bytes = stbi_load(image, &width, &height, &colorChannelNumber, 0);

        glGenTextures(1, &id);
        glBindTexture(textureType, id);

        glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(textureType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(textureType, GL_TEXTURE_WRAP_S, GL_NEAREST);
        glTexParameteri(textureType, GL_TEXTURE_WRAP_T, GL_NEAREST);

        glTexImage2D(textureType, 0, GL_RGBA, width, height, 0, format, pixelType, bytes);
        glGenerateMipmap(textureType);

        stbi_image_free(bytes);
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

    int GLTexture::get_width() const {
        return width;
    }
    
    int GLTexture::get_height() const {
        return height;
    }
}
