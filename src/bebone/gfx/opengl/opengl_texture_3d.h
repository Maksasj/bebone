#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_3D_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_3D_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    // Todo need testing
    class GLTexture3D : public GLTexture {
        private:
            int width;
            int height;
            int depth;

        public:
            GLTexture3D(const int& w, const int& h, const int& d, void* data);

            const int& get_width() const;
            const int& get_height() const;
            const int& get_depth() const;
    };
}

#endif
