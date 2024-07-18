#ifndef _BEBONE_RENDERER_IMATERIAL_MANAGER_H_
#define _BEBONE_RENDERER_IMATERIAL_MANAGER_H_

#include "renderer_backend.h"
#include "itexture.h"
#include "imaterial.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IMaterialManager {
        public:
            virtual ~IMaterialManager() = default;

            virtual std::optional<std::shared_ptr<IMaterial>> get_material(const MaterialHandle& handle) const = 0;
    };
}

#endif
