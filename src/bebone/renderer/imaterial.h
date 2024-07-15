#ifndef _BEBONE_RENDERER_IMATERIAL_H_
#define _BEBONE_RENDERER_IMATERIAL_H_

#include "renderer_backend.h"
#include "itexture.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IMaterial {
        private:
            std::string name;

        protected:
            std::shared_ptr<ITexture> albedo_map;
            std::shared_ptr<ITexture> ao_map;
            std::shared_ptr<ITexture> height_map;
            std::shared_ptr<ITexture> metallic_map;
            std::shared_ptr<ITexture> roughness_map;

        public:
            IMaterial(const std::string& name);
            virtual ~IMaterial() = default;


    };
}

#endif
