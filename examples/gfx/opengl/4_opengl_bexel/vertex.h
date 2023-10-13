#ifndef BEXEL_VERTEX_H
#define BEXEL_VERTEX_H

#include "bebone.h"

namespace bexel {
    using namespace bebone::core;
    using namespace bebone;
    using namespace std;
    using namespace bebone::gfx;
    using namespace bebone::gfx::opengl;

    struct Vertex {
        Vec3f pos;
        Vec3f color;
    };
}

#endif
