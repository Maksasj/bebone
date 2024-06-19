#ifndef _BEBONE_CORE_TYPES_MATRIX_2X2_TPP_
#define _BEBONE_CORE_TYPES_MATRIX_2X2_TPP_

#include "matrix.tpp"

namespace bebone::core {
    template<>
    struct Matrix<f32, 2, 2> {
        f32 e[2 * 2];

        inline f32& operator()(const size_t& row, const size_t& col);
        inline const f32& operator()(const size_t& row, const size_t& col) const;

        inline std::string to_string() const;

        inline static Matrix<f32, 2, 2> get_rotation_matrix(const f32 &rotationAngle);
        inline static Matrix<f32, 2, 2> get_zero_rotation_matrix();
    };
}

namespace bebone::core {
    inline f32& Matrix<f32, 2, 2>::operator()(const size_t& row, const size_t& col) {
        return e[2 * row + col];
    }

    inline const f32& Matrix<f32, 2, 2>::operator()(const size_t& row, const size_t& col) const {
        return e[2 * row + col];
    }

    inline std::string Matrix<f32, 2, 2>::to_string() const {
        std::stringstream ss;

        for(i32 i = 0; i < 2; ++i)
            ss << e[i] << " ";

        return ss.str();
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::get_rotation_matrix(const f32 &rotationAngle) {
        return { {(f32)cos(rotationAngle), -(f32)sin(rotationAngle), (f32)sin(rotationAngle), (f32)cos(rotationAngle)}};
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::get_zero_rotation_matrix() {
        return {{ 1, 0, 0, 1 }};
    }
}

#endif
