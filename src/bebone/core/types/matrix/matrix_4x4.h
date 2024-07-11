#ifndef _BEBONE_CORE_TYPES_MATRIX_4X4_TPP_
#define _BEBONE_CORE_TYPES_MATRIX_4X4_TPP_

#include "matrix.tpp"

namespace bebone::core {
    template<>
    struct Matrix<f32, 4, 4> {
    private:
        f32 e[4][4];

    public:
        Matrix() = default;

        Matrix(f32 n00, f32 n01, f32 n02, f32 n03,
               f32 n10, f32 n11, f32 n12, f32 n13,
               f32 n20, f32 n21, f32 n22, f32 n23,
               f32 n30, f32 n31, f32 n32, f32 n33);

        Matrix(const Vec4f& a, const Vec4f& b, const Vec4f& c, const Vec4f& d);

        inline static Matrix<f32, 4, 4> splat(const f32& value);
        inline static Matrix<f32, 4, 4> identity();
        inline static Matrix<f32, 4, 4> translation(const Vec3<f32>& vector);
        inline static Matrix<f32, 4, 4> scale(const f32& rate);
        
        inline static Matrix<f32, 4, 4> orthographic(const f32& right, const f32& left, const f32& bottom, const f32& top, const f32& near, const f32& far);
        inline static Matrix<f32, 4, 4> perspective(const f32& fovy, const f32& aspect, const f32& near, const f32& far);
        inline static Matrix<f32, 4, 4> view(const Vec3f& origin, const Vec3f& dir, const Vec3f& up);
        inline static Matrix<f32, 4, 4> look_at(const Vec3f& origin, const Vec3f& center, const Vec3f& up);

        inline static Matrix<f32, 4, 4> rotation_x(const f32& angle);
        inline static Matrix<f32, 4, 4> rotation_y(const f32& angle);
        inline static Matrix<f32, 4, 4> rotation_z(const f32& angle);

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

        Vec3f s = a.cross(b);
        Vec3f t = c.cross(d);
        Vec3f u = a * y - b * x;
        Vec3f v = c * w - d * z;

        f32 inv_det = 1.0f / (s.dot(v) + t.dot(u));
        s *= inv_det;
        t *= inv_det;
        u *= inv_det;
        v *= inv_det;

        Vec3f r0 = b.cross(v) + t * y;
        Vec3f r1 = v.cross(a) - t * x;
        Vec3f r2 = d.cross(u) + s * w;
        Vec3f r3 = u.cross(c) - s * z;

        return {
            r0.x, r0.y, r0.z, -b.dot(t),
            r1.x, r1.y, r1.z, a.dot(t),
            r2.x, r2.y, r2.z, -d.dot(s),
            r3.x, r3.y, r3.z, c.dot(s)
        };
    }

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::translation(const Vec3<f32>& vector) {
    //     #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
    //     return {{
    //         1.0f, 0.0f, 0.0f, vector.x,
    //         0.0f, 1.0f, 0.0f, vector.y,
    //         0.0f, 0.0f, 1.0f, vector.z,
    //         0.0f, 0.0f, 0.0f, 1.0f
    //     }};
    //     #else
    //     return {{
    //         1.0f, 0.0f, 0.0f, 0.0f,
    //         0.0f, 1.0f, 0.0f, 0.0f,
    //         0.0f, 0.0f, 1.0f, 0.0f,
    //         vector.x, vector.y, vector.z, 1.0f
    //     }};
    //     #endif
    // }

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::scale(const f32& rate) {
    //     return {{
    //         rate, 0.0f, 0.0f, 0.0f,
    //         0.0f, rate, 0.0f, 0.0f,
    //         0.0f, 0.0f, rate, 0.0f,
    //         0.0f, 0.0f, 0.0f, 1.0f
    //     }};
    // }

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::orthographic(const f32& right, const f32& left, const f32& bottom, const f32& top, const f32& near, const f32& far) {
    //     #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
    //     return {{
    //         2.0f / (right - left), 0.0f, 0.0f, 0.0f,
    //         0.0f, 2.0f / (bottom - top), 0.0f, 0.0f,
    //          0.0f, 0.0f, 1.0f / (far - near), 0.0f,
    //        - (right + left) / (right - left), - (bottom + top) / (bottom - top), near / (near - far), 1.0f
    //     }};
    //     #else
    //         #ifndef BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
    //             return {{
    //                 2.0f / (right - left), 0.0f, 0.0f, - (right + left) / (right - left),
    //                 0.0f, 2.0f / (bottom - top), 0.0f, - (bottom + top) / (bottom - top),
    //                 0.0f, 0.0f, 1.0f / (far - near), near / (near - far),
    //                 0.0f, 0.0f, 0.0f, 1.0f
    //             }};
    //         #else
    //             return {{
    //                 2.0f / (right - left), 0.0f, 0.0f, - (right + left) / (right - left),
    //                 0.0f, -2.0f / (bottom - top), 0.0f, - (bottom + top) / (bottom - top),
    //                 0.0f, 0.0f, 1.0f / (far - near), near / (near - far),
    //                 0.0f, 0.0f, 0.0f, 1.0f
    //             }};
    //         #endif
    //     #endif
    // }

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::perspective(const f32& fovy, const f32& aspect, const f32& near, const f32& far) {
    //     const f32 tanHalfFovy = std::tan(fovy / 2.f);
//
    //     #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
    //     return {{
    //         1.f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
    //         0.0f, 1.f / (tanHalfFovy), 0.0f, 0.0f,
    //         0.0f, 0.0f, far / (far - near), -(far * near) / (far - near),
    //         0.0f, 0.0f, 1.0f, 0.0f
    //     }};
    //     #else
    //         #ifndef BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
    //             return {{
    //                 1.f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
    //                 0.0f, 1.f / (tanHalfFovy), 0.0f, 0.0f,
    //                 0.0f, 0.0f, far / (far - near), 1.0f,
    //                 0.0f, 0.0f, -(far * near) / (far - near), 0.0f
    //             }};
    //         #else
    //             return {{
    //                 1.f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
    //                 0.0f, -1.f / (tanHalfFovy), 0.0f, 0.0f,
    //                 0.0f, 0.0f, far / (far - near), 1.0f,
    //                 0.0f, 0.0f, -(far * near) / (far - near), 0.0f
    //             }};
    //         #endif
    //     #endif
    // }

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::view(const Vec3f& origin, const Vec3f& dir, const Vec3f& up) {
    //     const auto w = dir.normalize();
    //     const auto u = w.cross(up).normalize();
    //     const auto v = w.cross(u);
//
    //     auto view_matrix = identity();
//
    //     view_matrix[0 * 4 + 0] = u.x;
    //     view_matrix[1 * 4 + 0] = u.y;
    //     view_matrix[2 * 4 + 0] = u.z;
    //     view_matrix[0 * 4 + 1] = v.x;
    //     view_matrix[1 * 4 + 1] = v.y;
    //     view_matrix[2 * 4 + 1] = v.z;
    //     view_matrix[0 * 4 + 2] = w.x;
    //     view_matrix[1 * 4 + 2] = w.y;
    //     view_matrix[2 * 4 + 2] = w.z;
    //     view_matrix[3 * 4 + 0] = -1.0f * (u).dot(origin);
    //     view_matrix[3 * 4 + 1] = -1.0f * (v).dot(origin);
    //     view_matrix[3 * 4 + 2] = -1.0f * (w).dot(origin);
//
    //     return view_matrix;
    // }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::look_at(const Vec3f& origin, const Vec3f& center, const Vec3f& up) {
        const auto dir = center - origin;
        return view(origin, dir, up);
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

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::rotation_x(const f32& angle) {
    //     const f32 cos0 = std::cos(angle);
    //     const f32 sin0 = std::sin(angle);
//
    //     #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
    //     return {{
    //         1.0f, 0.0f,  0.0f, 0.0f,
    //         0.0f, cos0, -sin0, 0.0f,
    //         0.0f, sin0,  cos0, 0.0f,
    //         0.0f, 0.0f,  0.0f, 1.0f
    //     }};
    //     #else
    //     return {{
    //         1.0f,  0.0f,  0.0f, 0.0f,
    //         0.0f,  cos0,  sin0, 0.0f,
    //         0.0f, -sin0,  cos0, 0.0f,
    //         0.0f,  0.0f,  0.0f, 1.0f
    //     }};
    //     #endif
    // }

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::rotation_y(const f32& angle) {
    //     const f32 cos0 = std::cos(angle);
    //     const f32 sin0 = std::sin(angle);
//
    //     #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
    //     return {{
    //             cos0, 0.0f, sin0, 0.0f,
    //             0.0f, 1.0f, 0.0f, 0.0f,
    //         -sin0, 0.0f, cos0, 0.0f,
    //             0.0f, 0.0f, 0.0f, 1.0f
    //     }};
    //     #else
    //     return {{
    //             cos0, 0.0f, -sin0, 0.0f,
    //             0.0f, 1.0f,  0.0f, 0.0f,
    //             sin0, 0.0f,  cos0, 0.0f,
    //             0.0f, 0.0f,  0.0f, 1.0f
    //     }};
    //     #endif
    // }

    // inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::rotation_z(const f32& angle) {
    //     const f32 cos0 = std::cos(angle);
    //     const f32 sin0 = std::sin(angle);
    //
    //     #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
    //     return {{
    //         cos0, -sin0, 0.0f, 0.0f,
    //         sin0,  cos0, 0.0f, 0.0f,
    //         0.0f,  0.0f, 1.0f, 0.0f,
    //         0.0f,  0.0f, 0.0f, 1.0f
    //     }};
    //     #else
    //     return {{
    //             cos0, sin0, 0.0f, 0.0f,
    //         -sin0, cos0, 0.0f, 0.0f,
    //             0.0f, 0.0f, 1.0f, 0.0f,
    //             0.0f, 0.0f, 0.0f, 1.0f
    //     }};
    //     #endif
    // }
}

#endif
