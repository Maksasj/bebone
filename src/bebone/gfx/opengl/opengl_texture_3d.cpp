#include "opengl_texture_3d.h"

namespace bebone::gfx::opengl {
    const int& GLTexture3D::get_width() const {
        return width;
    }

    const int& GLTexture3D::get_height() const {
        return height;
    }

    const int& GLTexture3D::get_depth() const {
        return depth;
    }
}
