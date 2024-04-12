#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_CUBE_MAP_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_CUBE_MAP_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    class GLTextureCubeMap : public GLTexture {
        private:

        public:

            /*
            GLTexture2D(const std::string& filePath) : GLTexture(filePath, GL_TEXTURE_2D) {

            }

            template<typename _Color>
            GLTexture2D(const std::shared_ptr<Image<_Color>>& image) : GLTexture(image, GL_TEXTURE_2D) {

            }
            */
    };
}

#endif
