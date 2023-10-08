#ifndef VERTEX_H
#define VERTEX_H

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

struct Vertex {
    Vec3f pos;
    Vec3f color;
};

#endif
