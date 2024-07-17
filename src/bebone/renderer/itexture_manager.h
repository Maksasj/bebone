#ifndef _BEBONE_RENDERER_ITEXTURE_MANAGER_H_
#define _BEBONE_RENDERER_ITEXTURE_MANAGER_H_

#include "renderer_backend.h"
#include "itexture.h"

namespace bebone::renderer {
    class ITextureManager {
        public:
            virtual ~ITextureManager() = default;

            virtual std::shared_ptr<ITexture> create_texture() = 0;
            virtual std::shared_ptr<ITexture> load_texture_from_file(const std::string& file_path) = 0;
    };
}

#endif
