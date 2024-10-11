#ifndef _BEBONE_RENDERER_TRANSFORM_H_
#define _BEBONE_RENDERER_TRANSFORM_H_

#include "vertex.h"

namespace bebone::renderer {
    using namespace bebone::core;

    struct Transform {
        Vec3f position = Vec3f::zero;
        Vec3f rotation = Vec3f::zero;
        Vec3f scale = Vec3f::zero; // Todo, rotation should not be a Vec3f
    };

    Mat4f calculate_transform_matrix(const Transform& transform);
}

#endif
