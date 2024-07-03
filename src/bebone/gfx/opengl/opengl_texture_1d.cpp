#include "opengl_texture_1d.h"

namespace bebone::gfx {
    GLTexture1D::GLTexture1D(const int& w, void* data)
            : GLTexture(GL_TEXTURE_1D),
              width(w)
    {
        bind();
        glTexImage1D(get_texture_type(), 0, 0, width, 0, GL_RGBA, GL_FLOAT, data);
        unbind();
    }

    const int& GLTexture1D::get_width() const {
        return width;
    }
}
