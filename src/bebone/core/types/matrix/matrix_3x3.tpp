#ifndef _BEBONE_CORE_TYPES_MATRIX_3X3_TPP_
#define _BEBONE_CORE_TYPES_MATRIX_3X3_TPP_

#include "matrix.tpp"

namespace bebone::core {
    template<>
    struct Matrix<f32, 3, 3> {
    private:
        f32 e[3][3];
    public:
        Matrix() = default;

        Matrix(f32 n00, f32 n01, f32 n02,
               f32 n10, f32 n11, f32 n12,
               f32 n20, f32 n21, f32 n22);

        Matrix(const Vec3f& a, const Vec3f& b, const Vec3f& c);

        inline f32& operator()(const size_t& row, const size_t& col);
        inline const f32& operator()(const size_t& row, const size_t& col) const;

        inline Vec2f& operator[](const size_t& col);
        inline const Vec2f& operator[](const size_t& col) const;

        inline std::string to_string() const;
    };
}

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

    inline f32& Matrix<f32, 3, 3>::operator()(const size_t& row, const size_t& col) {
        return e[col][row];
    }

    inline const f32& Matrix<f32, 3, 3>::operator()(const size_t& row, const size_t& col) const {
        return e[col][row];
    }

    inline Vec2f& Matrix<f32, 3, 3>::operator[](const size_t& col) {
        return (*reinterpret_cast<Vec2f*>(e[col]));
    }

    inline const Vec2f& Matrix<f32, 3, 3>::operator[](const size_t& col) const {
        return (*reinterpret_cast<const Vec2f*>(e[col]));
    }

    inline std::string Matrix<f32, 3, 3>::to_string() const {
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

#endif
