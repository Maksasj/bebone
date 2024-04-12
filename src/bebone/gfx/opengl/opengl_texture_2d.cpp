#include "opengl_texture_2d.h"

namespace bebone::gfx::opengl {
    const int& GLTexture2D::get_width() const {
        return width;
    }

    const int& GLTexture2D::get_height() const {
        return height;
    }
}
