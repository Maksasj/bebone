#ifndef _BEBONE_RENDERER_IMATERIAL_MANAGER_H_
#define _BEBONE_RENDERER_IMATERIAL_MANAGER_H_

#include "renderer_backend.h"
#include "itexture_impl.h"
#include "imaterial_impl.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IMaterialManager {
        public:
            virtual ~IMaterialManager() = default;

            virtual MaterialHandle get_default_material() = 0;
            virtual MaterialHandle create_material(void* properties, const size_t& size) = 0;

            virtual std::optional<std::shared_ptr<IMaterialImpl>> get_material(const MaterialHandle& handle) const = 0;
    };
}

#endif
