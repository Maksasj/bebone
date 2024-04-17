#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_1D_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_1D_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    // Todo need testing
    class GLTexture1D : public GLTexture {
        private:
            int width;

        public:
            GLTexture1D(const int& w, void* data);

            const int& get_width() const;
    };
}

#endif
