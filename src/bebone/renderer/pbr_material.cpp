#include "pbr_material.h"

namespace bebone::renderer {
    using namespace bebone::core;

    PBRMaterial::PBRMaterial(const std::string& name, const std::shared_ptr<ITexture> albedo) : IMaterial(name) {
        albedo_map = albedo;
    }
}
