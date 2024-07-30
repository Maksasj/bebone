#ifndef _BEBONE_RENDERER_IMATERIAL_H_
#define _BEBONE_RENDERER_IMATERIAL_H_

#include "renderer_backend.h"
#include "itexture.h"

namespace bebone::renderer {
    using namespace bebone::core;

    enum class MaterialHandle : u32 { Invalid = 0 };

    struct alignas(16) PBRMaterialProperties {
        TextureHandle albedo_handle;
        TextureHandle height_handle;
        TextureHandle metallic_handle;
        TextureHandle roughness_handle;
    };

    class IMaterial {
        public:
            virtual ~IMaterial() = default;

            virtual void set_properties(const void* properties) = 0;

            virtual const MaterialHandle& get_handle() const = 0;
    };
}

#endif
