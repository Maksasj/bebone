#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    GLTexture::GLTexture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
        int imageWidth;
        int imageHeight;
        int colorChannelNumber;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(image, &imageWidth, &imageHeight, &colorChannelNumber, 0);

        glGenTextures(1, &id);
        glActiveTexture(slot);
        glBindTexture(texType, id);

        glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_NEAREST);
        glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_NEAREST);

        glTexImage2D(texType, 0, GL_RGBA, imageWidth, imageHeight, 0, format, pixelType, bytes);
        glGenerateMipmap(texType);

        stbi_image_free(bytes);
        glBindTexture(texType, 0);
    }

    void GLTexture::bind() {
        glBindTexture(GL_TEXTURE_2D, id);
    }

    void GLTexture::unbind() {
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void GLTexture::destroy() {
        glDeleteTextures(1, &id);
    }
}
