#ifndef TRANSFORM_H
#define TRANSFORM_H

#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

using namespace bebone::gfx;
using namespace bebone::core;

struct Transform {
    Mat4f transform;
    Mat4f scale;
    Mat4f rotation;
};

#endif
