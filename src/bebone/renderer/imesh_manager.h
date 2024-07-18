#ifndef _BEBONE_RENDERER_IMESH_MANAGER_H_
#define _BEBONE_RENDERER_IMESH_MANAGER_H_

#include "renderer_backend.h"
#include "itexture.h"

namespace bebone::renderer {
    using namespace bebone::core;

    class IMeshManager {
        public:
            virtual ~IMeshManager() = default;
    };
}

#endif
