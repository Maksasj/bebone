#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_1D_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_1D_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    class GLTexture1D : public GLTexture {
        private:
            int width;

        public:
            /*
            GLTexture1D(const std::string& filePath) : GLTexture(filePath, GL_TEXTURE_2D) {

            }

            template<typename _Color>
            GLTexture1D(const std::shared_ptr<Image<_Color>>& image) : GLTexture(image, GL_TEXTURE_2D) {

            }
            */

            const int& get_width() const;
    };
}

#endif
