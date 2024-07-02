#ifndef BEXEL_TRANSFORM_H
#define BEXEL_TRANSFORM_H

#include "mesh/vertex.h"

namespace bexel {
    struct Transform {
        Vec3f translation;
        Mat4f rotation;
        Vec3f scale;

        Mat4f calc_matrix() const {
            return Mat4f::translation(translation);
        }
    };
}

#endif
