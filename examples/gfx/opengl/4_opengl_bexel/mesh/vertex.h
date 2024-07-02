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
            f32 result_x = pos.x * matrix.e[0 * 4 + 0] + pos.y * matrix.e[1 * 4 + 0] + pos.z * matrix.e[2 * 4 + 0] + 1.0f * matrix.e[3 * 4 + 0];
            f32 result_y = pos.x * matrix.e[0 * 4 + 1] + pos.y * matrix.e[1 * 4 + 1] + pos.z * matrix.e[2 * 4 + 1] + 1.0f * matrix.e[3 * 4 + 1];
            f32 result_z = pos.x * matrix.e[0 * 4 + 2] + pos.y * matrix.e[1 * 4 + 2] + pos.z * matrix.e[2 * 4 + 2] + 1.0f * matrix.e[3 * 4 + 2];
            const f32 result_w = pos.x * matrix.e[0 * 4 + 3] + pos.y * matrix.e[1 * 4 + 3] + pos.z * matrix.e[2 * 4 + 3] + 1.0f * matrix.e[3 * 4 + 3];

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
