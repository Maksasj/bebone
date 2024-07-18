#ifndef _BEBONE_RENDERER_IMATERIAL_H_
#define _BEBONE_RENDERER_IMATERIAL_H_

#include "renderer_backend.h"
#include "itexture.h"

namespace bebone::renderer {
    using namespace bebone::core;

    enum class MaterialHandle : u32 { Invalid = 0 };

    class IMaterialPropertyLayout {
        private:
            ColorRGBA albedo;
            f32 metalness;
        public:
    };

    class PBRMaterialPropertyLayout : public IMaterialPropertyLayout {

    };

    class MaterialProperties {

    };

    class IMaterial {
        public:
            virtual ~IMaterial() = default;

            virtual const MaterialHandle& get_handle() const = 0;
    };
}

#endif
