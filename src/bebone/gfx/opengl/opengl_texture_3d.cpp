#include "opengl_texture_3d.h"

namespace bebone::gfx {
    GLTexture3D::GLTexture3D(const int& w, const int& h, const int& d, void* data)
            : GLTexture(GL_TEXTURE_3D),
              width(w),
              height(h),
              depth(d)
    {
        bind();
        glTexImage3D(get_texture_type(), 0, 0, width, height, depth, 0, GL_RGBA, GL_FLOAT, data);
        unbind();
    }

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
