#ifndef _BEBONE_RENDERER_PBR_MATERIAL_H_
#define _BEBONE_RENDERER_PBR_MATERIAL_H_

#include "imaterial.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class PBRMaterial : public IMaterial {
        public:
            PBRMaterial(const std::string& name, const std::shared_ptr<ITexture> albedo);
    };
}

#endif
