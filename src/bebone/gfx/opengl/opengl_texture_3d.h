#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_3D_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_3D_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx {
    using namespace bebone::assets;

    // Todo need testing
    class GLTexture3D : public GLTexture {
        private:
            int width;
            int height;
            int depth;

        public:
            /*!
            * Constructor
            * @param w - texture width
            * @param h - texture height
            * @param d - texture depth
            * @param data - pointer to pixel data
            */
            GLTexture3D(const int& w, const int& h, const int& d, void* data);

            // Getter for image width
            const int& get_width() const;

            // Getter for image height
            const int& get_height() const;

            // Getter for image depth
            const int& get_depth() const;
    };
}

#endif
