#ifndef _BEBONE_RENDERER_IMATERIAL_H_
#define _BEBONE_RENDERER_IMATERIAL_H_

#include "imaterial_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    struct PBRMaterialProperties {
        TextureHandle albedo;
        TextureHandle height;
        TextureHandle metallic;
        TextureHandle roughness;
    };

    class IMaterial : private NonCopyable {
        private:
            std::shared_ptr<IMaterialImpl> impl;

        public:
            IMaterial(const std::shared_ptr<IMaterialImpl>& impl);

            MaterialHandle get_handle() const;
    };
}

#endif
