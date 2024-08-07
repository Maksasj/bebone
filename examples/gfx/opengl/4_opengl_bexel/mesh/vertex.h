#ifndef BEXEL_VERTEX_H
#define BEXEL_VERTEX_H

#include "bebone/bebone.h"

namespace bexel {
    using namespace std;
    using namespace bebone::core;
    using namespace bebone::gfx;

    struct Vertex {
        Vec3f pos;
        Vec2f tex;

        void translate(const Vec3f& value) {
            pos += value;
        }

        void scale(const Vec3f& rate) {
            pos *= rate;
        }

        void rotate(const Mat4f& matrix) {
            f32 result_x = Vec3f::dot(pos, (Vec3f)matrix[0]) + matrix(3, 0);
            f32 result_y = Vec3f::dot(pos, (Vec3f)matrix[1]) + matrix(3, 1);
            f32 result_z = Vec3f::dot(pos, (Vec3f)matrix[2]) + matrix(3, 2);
            const f32 result_w = Vec3f::dot(pos, (Vec3f)matrix[3]) + matrix(3, 3);

            if (result_w != 0.0f) {
                result_x /= result_w;
                result_y /= result_w;
                result_z /= result_w;
            }

            pos = Vec3f(result_x, result_y, result_z);
        }
    };
}

#endif
