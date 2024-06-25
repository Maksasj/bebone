#ifndef _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_CUBE_MAP_H_
#define _BEBONE_GFX_OPENGL_OPENGL_TEXTURE_CUBE_MAP_H_

#include "../../assets/image/image.h"

#include "../gfx_backend.h"

#include "opengl_texture.h"

namespace bebone::gfx::opengl {
    using namespace bebone::assets;

    class GLTextureCubeMap : public GLTexture {
        private:
            // Function that creates cube map from image array
            template<typename Color>
            void create_cube_map_texture(const std::array<std::shared_ptr<Image<Color>>, 6>& images);

        public:
            /*!
            * Constructor
            * @param file_paths - container with file paths for cube map texture, 6 textures required
            */
            GLTextureCubeMap(const std::vector<std::string>& file_paths);

            /*!
            * Constructor
            * @param images - 6 element array, with image for each cube side
            */
            template<typename Color>
            GLTextureCubeMap(const std::array<std::shared_ptr<Image<Color>>, 6>& images);
    };
}

#endif
