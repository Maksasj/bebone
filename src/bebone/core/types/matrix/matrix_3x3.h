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

        inline Vec3f& operator[](const size_t& col);
        inline const Vec3f& operator[](const size_t& col) const;

        inline Matrix<f32, 3, 3> operator +(const Matrix<f32, 3, 3>& other) const;
        inline Matrix<f32, 3, 3> operator -(const Matrix<f32, 3, 3>& other) const;
        inline Matrix<f32, 3, 3> operator *(const Matrix<f32, 3, 3>& other) const;

        inline Vec3f operator *(const Vec3f& v) const;

        inline Matrix<f32, 3, 3> operator +(const f32& scalar) const;
        inline Matrix<f32, 3, 3> operator -(const f32& scalar) const;
        inline Matrix<f32, 3, 3> operator *(const f32& scalar) const;
        inline Matrix<f32, 3, 3> operator /(f32 scalar) const;

        inline bool operator ==(const Matrix<f32, 3, 3>& other) const;

        std::string to_string() const;
    };

    inline f32& Matrix<f32, 3, 3>::operator()(const size_t& row, const size_t& col) {
        return e[col][row];
    }

    inline const f32& Matrix<f32, 3, 3>::operator()(const size_t& row, const size_t& col) const {
        return e[col][row];
    }

    inline Vec3f& Matrix<f32, 3, 3>::operator[](const size_t& col) {
        return (*reinterpret_cast<Vec3f*>(e[col]));
    }

    inline const Vec3f& Matrix<f32, 3, 3>::operator[](const size_t& col) const {
        return (*reinterpret_cast<const Vec3f*>(e[col]));
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

    inline Vec3f Matrix<f32, 3, 3>::operator *(const Vec3f& v) const {
        const Matrix<f32, 3, 3>& m = *this;

        return {
                m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z,
                m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z,
                m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z
        };
    }

    inline Matrix<f32, 3, 3> Matrix<f32, 3, 3>::operator +(const f32& scalar) const {
        const Matrix<f32, 3, 3>& m = *this;

        return {
                m(0, 0) + scalar, m(0, 1) + scalar, m(0, 2) + scalar,
                m(1, 0) + scalar, m(1, 1) + scalar, m(1, 2) + scalar,
                m(2, 0) + scalar, m(2, 1) + scalar, m(2, 2) + scalar
        };
    }

    inline Matrix<f32, 3, 3> Matrix<f32, 3, 3>::operator *(const f32& scalar) const {
        const Matrix<f32, 3, 3>& m = *this;

        return {
                m(0, 0) - scalar, m(0, 1) - scalar, m(0, 2) - scalar,
                m(1, 0) - scalar, m(1, 1) - scalar, m(1, 2) - scalar,
                m(2, 0) - scalar, m(2, 1) - scalar, m(2, 2) - scalar
        };
    }

    inline Matrix<f32, 3, 3> Matrix<f32, 3, 3>::operator /(f32 scalar) const {
        const Matrix<f32, 3, 3>& m = *this;
        scalar = 1.0f / scalar;

        return m * scalar;
    }

    inline bool Matrix<f32, 3, 3>::operator ==(const Matrix<f32, 3, 3>& other) const {
        const Matrix<f32, 3, 3>& m = *this;

        return m(0, 0) == other(0, 0) && m(0, 1) == other(0, 1) && m(0, 2) == other(0, 2) &&
               m(1, 0) == other(1, 0) && m(1, 1) == other(1, 1) && m(1, 2) == other(1, 2) &&
               m(2, 0) == other(2, 0) && m(2, 1) == other(2, 1) && m(2, 2) == other(2, 2);
    }
}

#endif
