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

        inline Matrix<f32, 2, 2> transpose() const;
        inline Matrix<f32, 2, 2> inverse() const;

        static Matrix<f32, 2, 2> get_rotation_matrix(const f32 &angle);

        inline f32& operator()(const size_t& row, const size_t& col);
        inline const f32& operator()(const size_t& row, const size_t& col) const;

        inline Vec2f& operator[](const size_t& col);
        inline const Vec2f& operator[](const size_t& col) const;

        inline Matrix<f32, 2, 2> operator +(const Matrix<f32, 2, 2>& other) const;
        inline Matrix<f32, 2, 2> operator -(const Matrix<f32, 2, 2>& other) const;
        inline Matrix<f32, 2, 2> operator *(const Matrix<f32, 2, 2>& other) const;

        inline Vec2f operator *(const Vec2f& v) const;

        inline Matrix<f32, 2, 2> operator +(const f32& scalar) const;
        inline Matrix<f32, 2, 2> operator -(const f32& scalar) const;
        inline Matrix<f32, 2, 2> operator *(const f32& scalar) const;
        inline Matrix<f32, 2, 2> operator /(f32 scalar) const;

        inline bool operator ==(const Matrix<f32, 2, 2>& other) const;

        std::string to_string() const;
    };

    inline f32& Matrix<f32, 2, 2>::operator()(const size_t& row, const size_t& col) {
        return e[col][row];
    }

    inline const f32& Matrix<f32, 2, 2>::operator()(const size_t& row, const size_t& col) const {
        return e[col][row];
    }

    inline Vec2f& Matrix<f32, 2, 2>::operator[](const size_t& col) {
        return (*reinterpret_cast<Vec2f*>(e[col]));
    }

    inline const Vec2f& Matrix<f32, 2, 2>::operator[](const size_t& col) const {
        return (*reinterpret_cast<const Vec2f*>(e[col]));
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::operator +(const Matrix<f32, 2, 2>& other) const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
                m(0, 0) + other(0, 0), m(0, 1) + other(0, 1),
                m(1, 0) + other(1, 0), m (1, 1) + other(1, 1)
        };
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::operator -(const Matrix<f32, 2, 2>& other) const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
                m(0, 0) - other(0, 0), m(0, 1) - other(0, 1),
                m(1, 0) - other(1, 0), m(1, 1) - other(1, 1)
        };
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::operator *(const Matrix<f32, 2, 2>& other) const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
                m(0, 0) * other(0, 0) + m(0, 1) * other(1, 0),
                m(0, 0) * other(0, 1) + m(0, 1) * other(1, 1),
                m(1, 0) * other(0, 0) + m(1, 1) * other(1, 0),
                m(1, 0) * other(0, 1) + m(1, 1) * other(1, 1)
        };
    }

    inline Vec2f Matrix<f32, 2, 2>::operator *(const Vec2f& v) const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
                m(0, 0) * v.x + m(0, 1) * v.y,
                m(1, 0) * v.x + m(1, 1) * v.y
        };
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::operator +(const f32& scalar) const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
                m(0, 0) + scalar, m(0, 1) + scalar,
                m(1, 0) + scalar, m(1, 1) + scalar
        };
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::operator -(const f32& scalar) const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
                m(0, 0) - scalar, m(0, 1) - scalar,
                m(1, 0) - scalar, m(1, 1) - scalar
        };
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::operator *(const f32& scalar) const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
                m(0, 0) * scalar, m(0, 1) * scalar,
                m(1, 0) * scalar, m(1, 1) * scalar
        };
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::operator /(f32 scalar) const {
        const Matrix<f32, 2, 2>& m = *this;
        scalar = 1.0f / scalar;

        return m * scalar;
    }

    inline bool Matrix<f32, 2, 2>::operator ==(const Matrix<f32, 2, 2>& other) const {
        const Matrix<f32, 2, 2>& m = *this;

        return m(0, 0) == other(0, 0) && m(0, 1) == other(0, 1) &&
            m(1, 0) == other(1, 0) && m(1, 1) == other(1, 1);
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::transpose() const {
        const Matrix<f32, 2, 2>& m = *this;

        return {
            m(0, 0), m(1, 0),
            m(0, 1), m(1, 1)
        };
    }

    inline Matrix<f32, 2, 2> Matrix<f32, 2, 2>::inverse() const {
        const Matrix<f32, 2, 2>& m = *this;

        const f32& a = m(0, 0);
        const f32& b = m(0, 1);
        const f32& c = m(1, 0);
        const f32& d = m(1, 1);

        f32 inv_det = 1.0f / (a * d - b * c);

        return {
            d * inv_det, -b * inv_det,
            -c * inv_det, a * inv_det
        };
    }
}

#endif
