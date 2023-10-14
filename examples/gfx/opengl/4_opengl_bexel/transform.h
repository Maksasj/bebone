#ifndef BEXEL_TRANSFORM_H
#define BEXEL_TRANSFORM_H

#include "vertex.h"

namespace bexel {
    struct Transform {
        Vec3f translation;

        Mat4f calc_matrix() const {
            return Mat4f::translation(translation);
        }
    };
}

#endif
