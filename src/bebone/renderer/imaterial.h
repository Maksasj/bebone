#ifndef _BEBONE_RENDERER_IMATERIAL_H_
#define _BEBONE_RENDERER_IMATERIAL_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class ITexture;

    class IMaterial {
        private:
            std::string name;

            std::shared_ptr<ITexture> albedo_texture;
            std::shared_ptr<ITexture> metallic_texture;
            std::shared_ptr<ITexture> roughness_texture;
            std::shared_ptr<ITexture> normal_texture;

        public:

    };
}

#endif
