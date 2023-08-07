#ifndef _BEBONE_COMMON_VERTEX_H_
#define _BEBONE_COMMON_VERTEX_H_

#include <vector>

namespace bebone::common {
    struct Vertex {
        float x;
        float y;

        float r = 1.0f;
        float g = 0.5f;
        float b = 1.0f;
    };
}

#endif
