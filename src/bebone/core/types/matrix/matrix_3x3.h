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

        inline Matrix<f32, 3, 3> operator +(const Matrix<f32, 3, 3>& other) const;
        inline Matrix<f32, 3, 3> operator -(const Matrix<f32, 3, 3>& other) const;
        inline Matrix<f32, 3, 3> operator *(const Matrix<f32, 3, 3>& other) const;
        inline Matrix<f32, 3, 3> operator *(const f32& scalar) const;
        inline Vec3f operator *(const Vec3f& v) const;

        std::string to_string() const;
    };

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

    inline Matrix<f32, 3, 3> Matrix<f32, 3, 3>::operator +(const Matrix<f32, 3, 3>& other) const {
        const Matrix<f32, 3, 3>& m = *this;

        return {
                m(0, 0) + other(0, 0), m(0, 1) + other(0, 1), m(0, 2) + other(0, 2),
                m(1, 0) + other(1, 0), m(1, 1) + other(1, 1), m(1, 2) + other(1, 2),
                m(2, 0) + other(2, 0), m(2, 1) + other(2, 1), m(2, 2) + other(2, 2)
        };
    }

    inline Matrix<f32, 3, 3> Matrix<f32, 3, 3>::operator -(const Matrix<f32, 3, 3>& other) const {
        const Matrix<f32, 3, 3>& m = *this;

        return {
                m(0, 0) - other(0, 0), m(0, 1) - other(0, 1), m(0, 2) - other(0, 2),
                m(1, 0) - other(1, 0), m(1, 1) - other(1, 1), m(1, 2) - other(1, 2),
                m(2, 0) - other(2, 0), m(2, 1) - other(2, 1), m(2, 2) - other(2, 2)
        };
    }

    inline Matrix<f32, 3, 3> Matrix<f32, 3, 3>::operator *(const Matrix<f32, 3, 3>& other) const {
        const Matrix<f32, 3, 3>& m = *this;

        return {
                m(0, 0) * other(0, 0) + m(0, 1) * other(1, 0) + m(0, 2) * other(2, 0),
                m(0, 0) * other(0, 1) + m(0, 1) * other(1, 1) + m(0, 2) * other(2, 1),
                m(0, 0) * other(0, 2) + m(0, 1) * other(1, 2) + m(0, 2) * other(2, 2),

                m(1, 0) * other(0, 0) + m(1, 1) * other(1, 0) + m(1, 2) * other(2, 0),
                m(1, 0) * other(0, 1) + m(1, 1) * other(1, 1) + m(1, 2) * other(2, 1),
                m(1, 0) * other(0, 2) + m(1, 1) * other(1, 2) + m(1, 2) * other(2, 2),

                m(2, 0) * other(0, 0) + m(2, 1) * other(1, 0) + m(2, 2) * other(2, 0),
                m(2, 0) * other(0, 1) + m(2, 1) * other(1, 1) + m(2, 2) * other(2, 1),
                m(2, 0) * other(0, 2) + m(2, 1) * other(1, 2) + m(2, 2) * other(2, 2)
        };
    }
}

#endif
