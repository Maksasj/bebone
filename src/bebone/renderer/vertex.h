#ifndef _BEBONE_RENDERER_VERTEX_H_
#define _BEBONE_RENDERER_VERTEX_H_

#include "renderer_backend.h"

namespace bebone::renderer {
    using namespace bebone::core;

    struct Vertex {
        Vec3f position; 
        Vec3f normal;
        Vec2f texcoord;
    };

    // tangent
    // bitangent
}

#endif
