#include "matrix_4x4.h"

namespace bebone::core {
    Matrix<f32, 4, 4>::Matrix(f32 n00, f32 n01, f32 n02, f32 n03,
                              f32 n10, f32 n11, f32 n12, f32 n13,
                              f32 n20, f32 n21, f32 n22, f32 n23,
                              f32 n30, f32 n31, f32 n32, f32 n33) {
        e[0][0] = n00; e[0][1] = n10; e[0][2] = n20; e[0][3] = n30;
        e[1][0] = n01; e[1][1] = n11; e[1][2] = n21; e[1][3] = n31;
        e[2][0] = n02; e[2][1] = n12; e[2][2] = n22; e[2][3] = n32;
        e[3][0] = n03; e[3][1] = n13; e[3][2] = n23; e[3][3] = n33;
    }

    Matrix<f32, 4, 4>::Matrix(const Vec4f &a, const Vec4f &b, const Vec4f &c, const Vec4f& d) {
        e[0][0] = a.x; e[0][1] = a.y; e[0][2] = a.z; e[0][3] = a.w;
        e[1][0] = b.x; e[1][1] = b.y; e[1][2] = b.z; e[1][3] = b.w;
        e[2][0] = c.x; e[2][1] = c.y; e[2][2] = c.z; e[2][3] = c.w;
        e[3][0] = d.x; e[3][1] = d.y; e[3][2] = d.z; e[3][3] = c.w;
    }

    const f32* Matrix<f32, 4, 4>::get_raw() const {
        return &e[0][0];
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_x(const f32& angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f,  c,   -s,   0.0f,
            0.0f,  s,    c,   0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_y(const f32& angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
             c,   0.0f,  s,   0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            -s,   0.0f,  c,   0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_z(const f32& angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
             c,   -s,   0.0f, 0.0f,
             s,    c,   0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    Matrix<f32, 4, 4> Matrix<f32, 4, 4>::get_rotation_matrix(const f32& angle, Vec3f axis) {
        if (!axis.is_normalized()) {
            axis = axis.normalize();
        }

        f32 c = std::cos(angle);
        f32 s = std::sin(angle);
        f32 d = 1.0f - c;

        f32 x = axis.x * d;
        f32 y = axis.y * d;
        f32 z = axis.z * d;

        f32 axay = x * axis.y;
        f32 axaz = x * axis.z;
        f32 ayaz = y * axis.z;

        return {
             c + x * axis.x,   axay - s * axis.z, axaz + s * axis.y, 0.0f,
            axay + s * axis.z,   c + y * axis.y,  ayaz - s * axis.x, 0.0f,
            axaz - s * axis.y, ayaz + s * axis.x,   c + z * axis.z,  0.0f,
                 0.0f,               0.0f,              0.0f,        1.0f
        };
    }

    std::string Matrix<f32, 4, 4>::to_string() const {
        std::stringstream ss;

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                ss << (*this)(i, j) << " ";
            }

            ss << std::endl;
        }

        return ss.str();
    }
}