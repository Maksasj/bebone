#ifndef _BEBONE_CORE_VERTEX_H_
#define _BEBONE_CORE_VERTEX_H_

#include "types.h"

namespace bebone::core {
    struct Vertex {
        Vec3f pos;
        Vec3f color;
        Vec2f texCoords;
        int norm;
    };
}

#endif
