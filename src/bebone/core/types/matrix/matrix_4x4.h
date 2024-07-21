#ifndef _BEBONE_CORE_TYPES_MATRIX_4X4_TPP_
#define _BEBONE_CORE_TYPES_MATRIX_4X4_TPP_

#include "matrix.tpp"

namespace bebone::core {
    template<>
    struct Matrix<f32, 4, 4> {
    public:
        f32 e[4][4];

    public:
        Matrix() = default;

        Matrix(const f32& n00, const f32& n01, const f32& n02, const f32& n03,
               const f32& n10, const f32& n11, const f32& n12, const f32& n13,
               const f32& n20, const f32& n21, const f32& n22, const f32& n23,
               const f32& n30, const f32& n31, const f32& n32, const f32& n33);

        Matrix(const Vec4f& a, const Vec4f& b, const Vec4f& c, const Vec4f& d);

        inline static Matrix<f32, 4, 4> splat(const f32& value);
        inline static Matrix<f32, 4, 4> identity();

        static Matrix<f32, 4, 4> get_rotation_x(const f32& angle);
        static Matrix<f32, 4, 4> get_rotation_y(const f32& angle);
        static Matrix<f32, 4, 4> get_rotation_z(const f32& angle);
        static Matrix<f32, 4, 4> get_rotation_matrix(const f32& angle, Vec3f axis);
        static Matrix<f32, 4, 4> get_reflection_matrix(const Vec3f& v);
        static Matrix<f32, 4, 4> get_involution_matrix(const Vec3f& v);

        static Matrix<f32, 4, 4> skew(f32 t, Vec3f a, Vec3f b);

        static Matrix<f32, 4, 4> scale(const f32& s);
        static Matrix<f32, 4, 4> scale(const f32& sx, const f32& sy, const f32& sz);
        static Matrix<f32, 4, 4> scale(const Vec3f& s);
        static Matrix<f32, 4, 4> scale(f32 s, Vec3f v);

        static Matrix<f32, 4, 4> translation(const f32& tx, const f32& ty, const f32& tz);
        static Matrix<f32, 4, 4> translation(const Vec3f& t);

        static Matrix<f32, 4, 4> orthographic(const f32& right, const f32& left, const f32& bottom, const f32& top, const f32& near, const f32& far);
        static Matrix<f32, 4, 4> perspective(f32 fov, const f32& aspect, const f32& near, const f32& far);
        static Matrix<f32, 4, 4> view(const Vec3f& origin, const Vec3f& direction, const Vec3f& up = Vec3f::up);
        static Matrix<f32, 4, 4> look_at(const Vec3f origin, const Vec3f center, const Vec3f& up = Vec3f::up);

        inline Matrix<f32, 4, 4> transpose() const;
        inline Matrix<f32, 4, 4> inverse() const;

        inline f32& operator()(const size_t& row, const size_t& col);
        inline const f32& operator()(const size_t& row, const size_t& col) const;

        inline Vec4f& operator[](const size_t& col);
        inline const Vec4f& operator[](const size_t& col) const;

        inline Matrix<f32, 4, 4> operator +(const Matrix<f32, 4, 4>& other) const;
        inline Matrix<f32, 4, 4> operator -(const Matrix<f32, 4, 4>& other) const;
        inline Matrix<f32, 4, 4> operator *(const Matrix<f32, 4, 4>& other) const;
        inline Vec4f operator *(const Vec4f& v) const;

        inline Matrix<f32, 4, 4> operator+(const f32& scalar) const;
        inline Matrix<f32, 4, 4> operator-(const f32& scalar) const;
        inline Matrix<f32, 4, 4> operator*(const f32& scalar) const;
        inline Matrix<f32, 4, 4> operator/(f32 scalar) const;

        inline bool operator==(const Matrix<f32, 4, 4>& other) const;
        inline bool operator!=(const Matrix<f32, 4, 4>& other) const;

        std::string to_string() const;
        const f32* get_raw() const;
    };

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::splat(const f32& value) {
        return {
            value, value, value, value,
            value, value, value, value,
            value, value, value, value,
            value, value, value, value
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::identity() {
        return {
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::transpose() const {
        const Matrix<f32, 4, 4>& m = *this;

        return {
                m(0, 0), m(1, 0), m(2, 0), m(3, 0),
                m(0, 1), m(1, 1), m(2, 1), m(3, 1),
                m(0, 2), m(1, 2), m(2, 2), m(3, 2),
                m(0, 3), m(1, 3), m(2, 3), m(3, 3)
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::inverse() const {
        const Matrix<f32, 4, 4>& m = *this;

        const Vec3f& a = reinterpret_cast<const Vec3f&>(m[0]);
        const Vec3f& b = reinterpret_cast<const Vec3f&>(m[1]);
        const Vec3f& c = reinterpret_cast<const Vec3f&>(m[2]);
        const Vec3f& d = reinterpret_cast<const Vec3f&>(m[3]);

        const float& x = m(3, 0);
        const float& y = m(3, 1);
        const float& z = m(3, 2);
        const float& w = m(3, 3);

        Vec3f s = Vec3f::cross(a, b);
        Vec3f t = Vec3f::cross(c, d);
        Vec3f u = a * y - b * x;
        Vec3f v = c * w - d * z;

        f32 inv_det = 1.0f / (Vec3f::dot(s, v) + Vec3f::dot(t, u));
        s *= inv_det;
        t *= inv_det;
        u *= inv_det;
        v *= inv_det;

        Vec3f r0 = Vec3f::cross(b, v) + t * y;
        Vec3f r1 = Vec3f::cross(v, a) - t * x;
        Vec3f r2 = Vec3f::cross(d, u) + s * w;
        Vec3f r3 = Vec3f::cross(u, c) - s * z;

        return {
            r0.x, r0.y, r0.z, Vec3f::dot(-b, t),
            r1.x, r1.y, r1.z, Vec3f::dot(a, t),
            r2.x, r2.y, r2.z, Vec3f::dot(-d, s),
            r3.x, r3.y, r3.z, Vec3f::dot(c, s)
        };
    }

    inline f32& Matrix<f32, 4, 4>::operator()(const size_t& row, const size_t& col) {
        return e[col][row];
    }

    inline const f32& Matrix<f32, 4, 4>::operator()(const size_t& row, const size_t& col) const {
        return e[col][row];
    }

    inline Vec4f& Matrix<f32, 4, 4>::operator[](const size_t& col) {
        return (*reinterpret_cast<Vec4f*>(e[col]));
    }

    inline const Vec4f& Matrix<f32, 4, 4>::operator[](const size_t& col) const {
        return (*reinterpret_cast<const Vec4f*>(e[col]));
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator +(const Matrix<f32, 4, 4>& other) const {
        const Matrix<f32, 4, 4>& m = *this;

        return {
                m(0, 0) + other(0, 0), m(0, 1) + other(0, 1), m(0, 2) + other(0, 2), m(0, 3) + other(0, 3),
                m(1, 0) + other(1, 0), m(1, 1) + other(1, 1), m(1, 2) + other(1, 2), m(1, 3) + other(1, 3),
                m(2, 0) + other(2, 0), m(2, 1) + other(2, 1), m(2, 2) + other(2, 2), m(2, 3) + other(2, 3),
                m(3, 0) + other(3, 0), m(3, 1) + other(3, 1), m(3, 2) + other(3, 2), m(3, 3) + other(3, 3)
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator -(const Matrix<f32, 4, 4>& other) const {
        const Matrix<f32, 4, 4>& m = *this;

        return {
                m(0, 0) - other(0, 0), m(0, 1) - other(0, 1), m(0, 2) - other(0, 2), m(0, 3) - other(0, 3),
                m(1, 0) - other(1, 0), m(1, 1) - other(1, 1), m(1, 2) - other(1, 2), m(1, 3) - other(1, 3),
                m(2, 0) - other(2, 0), m(2, 1) - other(2, 1), m(2, 2) - other(2, 2), m(2, 3) - other(2, 3),
                m(3, 0) - other(3, 0), m(3, 1) - other(3, 1), m(3, 2) - other(3, 2), m(3, 3) - other(3, 3)
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator *(const Matrix<f32, 4, 4>& other) const {
        const Matrix<f32, 4, 4>& m = *this;

        return {
                m(0, 0) * other(0, 0) + m(0, 1) * other(1, 0) + m(0, 2) * other(2, 0) + m(0, 3) * other(3, 0),
                m(0, 0) * other(0, 1) + m(0, 1) * other(1, 1) + m(0, 2) * other(2, 1) + m(0, 3) * other(3, 1),
                m(0, 0) * other(0, 2) + m(0, 1) * other(1, 2) + m(0, 2) * other(2, 2) + m(0, 3) * other(3, 2),
                m(0, 0) * other(0, 3) + m(0, 1) * other(1, 3) + m(0, 2) * other(2, 3) + m(0, 3) * other(3, 3),

                m(1, 0) * other(0, 0) + m(1, 1) * other(1, 0) + m(1, 2) * other(2, 0) + m(1, 3) * other(3, 0),
                m(1, 0) * other(0, 1) + m(1, 1) * other(1, 1) + m(1, 2) * other(2, 1) + m(1, 3) * other(3, 1),
                m(1, 0) * other(0, 2) + m(1, 1) * other(1, 2) + m(1, 2) * other(2, 2) + m(1, 3) * other(3, 2),
                m(1, 0) * other(0, 3) + m(1, 1) * other(1, 3) + m(1, 2) * other(2, 3) + m(1, 3) * other(3, 3),

                m(2, 0) * other(0, 0) + m(2, 1) * other(1, 0) + m(2, 2) * other(2, 0) + m(2, 3) * other(3, 0),
                m(2, 0) * other(0, 1) + m(2, 1) * other(1, 1) + m(2, 2) * other(2, 1) + m(2, 3) * other(3, 1),
                m(2, 0) * other(0, 2) + m(2, 1) * other(1, 2) + m(2, 2) * other(2, 2) + m(2, 3) * other(3, 2),
                m(2, 0) * other(0, 3) + m(2, 1) * other(1, 3) + m(2, 2) * other(2, 3) + m(2, 3) * other(3, 3),

                m(3, 0) * other(0, 0) + m(3, 1) * other(1, 0) + m(3, 2) * other(2, 0) + m(3, 3) * other(3, 0),
                m(3, 0) * other(0, 1) + m(3, 1) * other(1, 1) + m(3, 2) * other(2, 1) + m(3, 3) * other(3, 1),
                m(3, 0) * other(0, 2) + m(3, 1) * other(1, 2) + m(3, 2) * other(2, 2) + m(3, 3) * other(3, 2),
                m(3, 0) * other(0, 3) + m(3, 1) * other(1, 3) + m(3, 2) * other(2, 3) + m(3, 3) * other(3, 3)
        };
    }

    inline Vec4f Matrix<f32, 4, 4>::operator *(const Vec4f& v) const {
        const Matrix<f32, 4, 4>& m = *this;

        return {
                m(0, 0) * v.x + m(0, 1) * v.y + m(0, 2) * v.z + m(0, 3) * v.w,
                m(1, 0) * v.x + m(1, 1) * v.y + m(1, 2) * v.z + m(1, 3) * v.w,
                m(2, 0) * v.x + m(2, 1) * v.y + m(2, 2) * v.z + m(2, 3) * v.w,
                m(3, 0) * v.x + m(3, 1) * v.y + m(3, 2) * v.z + m(3, 3) * v.w
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator*(const f32& scalar) const {
        Matrix<f32, 4, 4> m = *this;

        return {
                m(0, 0) * scalar, m(0, 1) * scalar, m(0, 2) * scalar, m(0, 3) * scalar,
                m(1, 0) * scalar, m(1, 1) * scalar, m(1, 2) * scalar, m(1, 3) * scalar,
                m(2, 0) * scalar, m(2, 1) * scalar, m(2, 2) * scalar, m(2, 3) * scalar,
                m(3, 0) * scalar, m(3, 1) * scalar, m(3, 2) * scalar, m(3, 3) * scalar
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator/(f32 scalar) const {
        Matrix<f32, 4, 4> m = *this;
        scalar = 1.0f / scalar;

        return m * scalar;
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator+(const f32& scalar) const {
        Matrix<f32, 4, 4> m = *this;

        return {
                m(0, 0) + scalar, m(0, 1) + scalar, m(0, 2) + scalar, m(0, 3) + scalar,
                m(1, 0) + scalar, m(1, 1) + scalar, m(1, 2) + scalar, m(1, 3) + scalar,
                m(2, 0) + scalar, m(2, 1) + scalar, m(2, 2) + scalar, m(2, 3) + scalar,
                m(3, 0) + scalar, m(3, 1) + scalar, m(3, 2) + scalar, m(3, 3) + scalar
        };
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator-(const f32& scalar) const {
        Matrix<f32, 4, 4> m = *this;

        return {
                m(0, 0) - scalar, m(0, 1) - scalar, m(0, 2) - scalar, m(0, 3) - scalar,
                m(1, 0) - scalar, m(1, 1) - scalar, m(1, 2) - scalar, m(1, 3) - scalar,
                m(2, 0) - scalar, m(2, 1) - scalar, m(2, 2) - scalar, m(2, 3) - scalar,
                m(3, 0) - scalar, m(3, 1) - scalar, m(3, 2) - scalar, m(3, 3) - scalar
        };
    }

    inline bool Matrix<f32, 4, 4>::operator==(const Matrix<f32, 4, 4>& other) const {
        Matrix<f32, 4, 4> m = *this;

        return m(0, 0) == other(0, 0) && m(0, 1) == other(0, 1) && m(0, 2) == other(0, 2) && m(0, 3) == other(0, 3) &&
               m(1, 0) == other(1, 0) && m(1, 1) == other(1, 1) && m(1, 2) == other(1, 2) && m(1, 3) == other(1, 3) &&
               m(2, 0) == other(2, 0) && m(2, 1) == other(2, 1) && m(2, 2) == other(2, 2) && m(2, 3) == other(2, 3) &&
               m(3, 0) == other(3, 0) && m(3, 1) == other(3, 1) && m(3, 2) == other(3, 2) && m(3, 3) == other(3, 3);
    }

    inline bool Matrix<f32, 4, 4>::operator!=(const Matrix<f32, 4, 4>& other) const {
        return !(*this == other);
    }
}

#endif
