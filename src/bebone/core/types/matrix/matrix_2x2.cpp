#include "matrix_2x2.h"

namespace bebone::core {
    Matrix<f32, 2, 2>::Matrix(f32 n00, f32 n01, f32 n10, f32 n11) {
        e[0][0] = n00; e[0][1] = n10;
        e[1][0] = n01; e[1][1] = n11;
    }

    Matrix<f32, 2, 2>::Matrix(const Vec2f& a, const Vec2f& b) {
        e[0][0] = a.x; e[0][1] = a.y;
        e[1][0] = b.x; e[1][1] = b.y;
    }

    Matrix<f32, 2, 2> Matrix<f32, 2, 2>::get_rotation_matrix(const f32& angle) {
        f32 c = std::cos(angle);
        f32 s = std::sin(angle);

        return {
            c, -s,
            s,  c
        };
    }

    std::string Matrix<f32, 2, 2>::to_string() const {
        std::stringstream ss;

        for (i32 i = 0; i < 2; ++i) {
            for (auto j : e) {
                ss << j[i] << " ";
            }
            ss << std::endl;
        }

        return ss.str();
    }
}