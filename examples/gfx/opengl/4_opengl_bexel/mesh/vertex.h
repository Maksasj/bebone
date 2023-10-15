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

        void translate(const Vec3f& value) {
            pos += value;
        }

        void scale(const Vec3f& rate) {
            pos *= rate;
        }

        void rotate(const Mat4f& matrix) {
            f32 resultX = pos.x * matrix.e[0 * 4 + 0] + pos.y * matrix.e[1 * 4 + 0] + pos.z * matrix.e[2 * 4 + 0] + 1.0f * matrix.e[3 * 4 + 0];
            f32 resultY = pos.x * matrix.e[0 * 4 + 1] + pos.y * matrix.e[1 * 4 + 1] + pos.z * matrix.e[2 * 4 + 1] + 1.0f * matrix.e[3 * 4 + 1];
            f32 resultZ = pos.x * matrix.e[0 * 4 + 2] + pos.y * matrix.e[1 * 4 + 2] + pos.z * matrix.e[2 * 4 + 2] + 1.0f * matrix.e[3 * 4 + 2];
            const f32 resultW = pos.x * matrix.e[0 * 4 + 3] + pos.y * matrix.e[1 * 4 + 3] + pos.z * matrix.e[2 * 4 + 3] + 1.0f * matrix.e[3 * 4 + 3];

            if (resultW != 0.0f) {
                resultX /= resultW;
                resultY /= resultW;
                resultZ /= resultW;
            }

            pos = Vec3f(resultX, resultY, resultZ);
        }
    };
}

#endif
