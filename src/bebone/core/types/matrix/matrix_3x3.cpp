#include "matrix_3x3.h"

namespace bebone::core {
    Matrix<f32, 3, 3>::Matrix(f32 n00, f32 n01, f32 n02,
                              f32 n10, f32 n11, f32 n12,
                              f32 n20, f32 n21, f32 n22) {
        e[0][0] = n00; e[0][1] = n10; e[0][2] = n20;
        e[1][0] = n01; e[1][1] = n11; e[1][2] = n21;
        e[2][0] = n02; e[2][1] = n12; e[2][2] = n22;
    }

    Matrix<f32, 3, 3>::Matrix(const Vec3f &a, const Vec3f &b, const Vec3f &c) {
        e[0][0] = a.x; e[0][1] = a.y; e[0][2] = a.z;
        e[1][0] = b.x; e[1][1] = b.y; e[1][2] = b.z;
        e[2][0] = c.x; e[2][1] = c.y; e[2][2] = c.z;
    }

    Matrix<f32, 3, 3> Matrix<f32, 3, 3>::get_rotation_x(const f32 &angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
            1.0f, 0.0f, 0.0f,
            0.0f,  c,   -s,
            0.0f,  s,    c
        };
    }

    Matrix<f32, 3, 3> Matrix<f32, 3, 3>::get_rotation_y(const f32 &angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
            c,   0.0f,  s,
            0.0f, 1.0f, 0.0f,
            -s,   0.0f,  c
        };
    }

    Matrix<f32, 3, 3> Matrix<f32, 3, 3>::get_rotation_z(const f32 &angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
            c,   -s,   0.0f,
            s,    c,   0.0f,
            0.0f, 0.0f, 1.0f
        };
    }

    std::string Matrix<f32, 3, 3>::to_string() const {
        std::stringstream ss;

        for (i32 i = 0; i < 3; ++i) {
            for (i32 j = 0; j < 3; ++j) {
                ss << e[j][i] << " ";
            }
            ss << std::endl;
        }

        return ss.str();
    }
}