#ifndef _BEBONE_CORE_TYPES_MATRIX_2X2_TPP_
#define _BEBONE_CORE_TYPES_MATRIX_2X2_TPP_

#include "matrix.tpp"

namespace bebone::core {
    template<>
    struct Matrix<f32, 2, 2> {
    private:
        f32 e[2][2];
    public:
        Matrix() = default;

        Matrix(f32 n00, f32 n01,
               f32 n10, f32 n11);

        Matrix(const Vec2f& a, const Vec2f& b);

        inline f32& operator()(const size_t& row, const size_t& col);
        inline const f32& operator()(const size_t& row, const size_t& col) const;

        inline Vec2f& operator[](const size_t& row);
        inline const Vec2f& operator[](const size_t& row) const;

        inline std::string to_string() const;

        inline static Matrix<f32, 2, 2> get_rotation_matrix(const f32 &rotationAngle);
        inline static Matrix<f32, 2, 2> get_zero_rotation_matrix();
    };
}

namespace bebone::core {
    Matrix<f32, 2, 2>::Matrix(f32 n00, f32 n01, f32 n10, f32 n11) {
        e[0][0] = n00; e[0][1] = n01;
        e[1][0] = n10; e[1][1] = n11;
    }

    Matrix<f32, 2, 2>::Matrix(const Vec2f& a, const Vec2f& b) {
        e[0][0] = a.x; e[0][1] = a.y;
        e[1][0] = b.x; e[1][1] = b.y;
    }

    inline f32& Matrix<f32, 2, 2>::operator()(const size_t& row, const size_t& col) {
        return e[col][row];
    }

    inline const f32& Matrix<f32, 2, 2>::operator()(const size_t& row, const size_t& col) const {
        return e[col][row];
    }

    inline Vec2f& Matrix<f32, 2, 2>::operator[](const size_t& row) {
        return (*reinterpret_cast<Vec2f*>(e[row]));
    }

    inline const Vec2f& Matrix<f32, 2, 2>::operator[](const size_t& row) const {
        return (*reinterpret_cast<const Vec2f*>(e[row]));
    }

    inline std::string Matrix<f32, 2, 2>::to_string() const {
        std::stringstream ss;

        for (auto i : e) {
            for (i32 j = 0; j < 2; ++j) {
                ss << i[j] << " ";
            }
            ss << std::endl;
        }

        return ss.str();
    }

    // inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::get_rotation_matrix(const f32 &rotationAngle) {
    //     return { {(f32)cos(rotationAngle), -(f32)sin(rotationAngle), (f32)sin(rotationAngle), (f32)cos(rotationAngle)}};
    // }
//
    // inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::get_zero_rotation_matrix() {
    //     return {{ 1, 0, 0, 1 }};
    // }
}

#endif
