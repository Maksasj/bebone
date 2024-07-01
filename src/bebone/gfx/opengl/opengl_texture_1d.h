#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_1D_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_1D_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx {
    using namespace bebone::assets;

    // Todo need testing
    class GLTexture1D : public GLTexture {
        private:
            int width;

        public:
            /*!
            * Default GLTexture1D constructor
            * @param w - Texture width
            * @param data - Pointer to pixel data
            */
            GLTexture1D(const int& w, void* data);

            // Getter for image width
            const int& get_width() const;
    };
}

#endif
