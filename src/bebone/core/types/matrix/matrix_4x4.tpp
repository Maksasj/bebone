#ifndef _BEBONE_CORE_TYPES_MATRIX_4X4_TPP_
#define _BEBONE_CORE_TYPES_MATRIX_4X4_TPP_

#include "matrix.tpp"

namespace bebone::core {
    template<>
    struct Matrix<f32, 4, 4> {
        f32 e[4 * 4];

        inline static Matrix<f32, 4, 4> splat(const f32& value);
        inline static Matrix<f32, 4, 4> identity();
        inline static Matrix<f32, 4, 4> translation(const Vec3<f32>& vector);
        inline static Matrix<f32, 4, 4> scale(const f32& rate);
        inline static Matrix<f32, 4, 4> orthographic(const f32& right, const f32& left, const f32& bottom, const f32& top, const f32& near, const f32& far);
        inline static Matrix<f32, 4, 4> perspective(const f32& fovy, const f32& aspect, const f32& near, const f32& far);

        inline static Matrix<f32, 4, 4> rotation_x(const f32& angle);
        inline static Matrix<f32, 4, 4> rotation_y(const f32& angle);
        inline static Matrix<f32, 4, 4> rotation_z(const f32& angle);

        inline static Matrix<f32, 4, 4> transpose(const Matrix<f32, 4, 4>& matrix);
        inline void transpose();

        // Todo optimse, or use something like simd
        inline Matrix<f32, 4, 4> operator*(const Matrix<f32, 4, 4>& b) const;

        f32& operator[](const size_t& index);
        const f32& operator[](const size_t& index) const;

        inline Vec4<f32> operator*(const Vec4<f32>& vec) const {
            return {
                vec.x * e[0] + vec.y * e[4] + vec.z * e[8] + vec.w * e[12],
                vec.x * e[1] + vec.y * e[5] + vec.z * e[9] + vec.w * e[13],
                vec.x * e[2] + vec.y * e[6] + vec.z * e[10] + vec.w * e[14],
                vec.x * e[3] + vec.y * e[7] + vec.z * e[11] + vec.w * e[15]
            };
        }

        inline Matrix<f32, 4, 4> operator+(const f32& value) const;
        inline Matrix<f32, 4, 4> operator-(const f32& value) const;
        inline Matrix<f32, 4, 4> operator*(const f32& value) const;
        inline Matrix<f32, 4, 4> operator/(const f32& value) const;

        inline bool operator==(const Matrix<f32, 4, 4>& other) const;
        inline bool operator!=(const Matrix<f32, 4, 4>& other) const;

        inline std::string to_string() const;
    };
}

namespace bebone::core {
    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::splat(const f32& value) {
        return {{
            value, value, value, value,
            value, value, value, value,
            value, value, value, value,
            value, value, value, value
        }};
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::identity() {
        return {{
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }};
    }

    inline f32& Matrix<f32, 4, 4>::operator[](const size_t& index) {
        return e[index];
    }

    inline const f32& Matrix<f32, 4, 4>::operator[](const size_t& index) const {
        return e[index];
    }

    inline void Matrix<f32, 4, 4>::transpose() {
        const Matrix<f32, 4, 4> old = *this;
        *this = transpose(old);
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::transpose(const Matrix<f32, 4, 4>& matrix) {
        return {{
            matrix[0], matrix[4], matrix[8], matrix[12],
            matrix[1], matrix[5], matrix[9], matrix[13],
            matrix[2], matrix[6], matrix[10], matrix[14],
            matrix[3], matrix[7], matrix[11], matrix[15]
        }};
    }


    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::translation(const Vec3<f32>& vector) {
        #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
        return {{
            1.0f, 0.0f, 0.0f, vector.x,
            0.0f, 1.0f, 0.0f, vector.y,
            0.0f, 0.0f, 1.0f, vector.z,
            0.0f, 0.0f, 0.0f, 1.0f
        }};
        #else
        return {{
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            vector.x, vector.y, vector.z, 1.0f
        }};
        #endif
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::scale(const f32& rate) {
        return {{
            rate, 0.0f, 0.0f, 0.0f,
            0.0f, rate, 0.0f, 0.0f,
            0.0f, 0.0f, rate, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f
        }};
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::orthographic(const f32& right, const f32& left, const f32& bottom, const f32& top, const f32& near, const f32& far) {
        #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
        return {{
            2.0f / (right - left), 0.0f, 0.0f, 0.0f,
            0.0f, 2.0f / (bottom - top), 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f / (far - near), 0.0f,
            - (right + left) / (right - left), - (bottom + top) / (bottom - top), near / (near - far), 1.0f
        }};
        #else
            #ifndef BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
                return {{
                    2.0f / (right - left), 0.0f, 0.0f, - (right + left) / (right - left),
                    0.0f, 2.0f / (bottom - top), 0.0f, - (bottom + top) / (bottom - top),
                    0.0f, 0.0f, 1.0f / (far - near), near / (near - far),
                    0.0f, 0.0f, 0.0f, 1.0f
                }};
            #else
                return {{
                    2.0f / (right - left), 0.0f, 0.0f, - (right + left) / (right - left),
                    0.0f, -2.0f / (bottom - top), 0.0f, - (bottom + top) / (bottom - top),
                    0.0f, 0.0f, 1.0f / (far - near), near / (near - far),
                    0.0f, 0.0f, 0.0f, 1.0f
                }};
            #endif
        #endif
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::perspective(const f32& fovy, const f32& aspect, const f32& near, const f32& far) {
        const f32 tanHalfFovy = std::tan(fovy / 2.f);

        #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
        return {{
            1.f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
            0.0f, 1.f / (tanHalfFovy), 0.0f, 0.0f,
            0.0f, 0.0f, far / (far - near), -(far * near) / (far - near),
            0.0f, 0.0f, 1.0f, 0.0f
        }};
        #else
            #ifndef BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
                return {{
                    1.f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
                    0.0f, 1.f / (tanHalfFovy), 0.0f, 0.0f,
                    0.0f, 0.0f, far / (far - near), 1.0f,
                    0.0f, 0.0f, -(far * near) / (far - near), 0.0f
                }};
            #else
                return {{
                    1.f / (aspect * tanHalfFovy), 0.0f, 0.0f, 0.0f,
                    0.0f, -1.f / (tanHalfFovy), 0.0f, 0.0f,
                    0.0f, 0.0f, far / (far - near), 1.0f,
                    0.0f, 0.0f, -(far * near) / (far - near), 0.0f
                }};
            #endif
        #endif
    }

    inline std::string Matrix<f32, 4, 4>::to_string() const {
        std::stringstream ss;

        for(const f32& i : e)
            ss << i << " ";
        
        return ss.str();
    }

    // Todo optimse, or use something like simd
    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator*(const Matrix<f32, 4, 4>& b) const {
        return {{ 
            e[0]    * b.e[0] + e[1]     * b.e[4] + e[2]     * b.e[8]        + e[3]  * b.e[12], 
            e[0]    * b.e[1] + e[1]     * b.e[5] + e[2]     * b.e[9]        + e[3]  * b.e[13], 
            e[0]    * b.e[2] + e[1]     * b.e[6] + e[2]     * b.e[10]       + e[3]  * b.e[14], 
            e[0]    * b.e[3] + e[1]     * b.e[7] + e[2]     * b.e[11]       + e[3]  * b.e[15], 
            e[4]    * b.e[0] + e[5]     * b.e[4] + e[6]     * b.e[8]        + e[7]  * b.e[12], 
            e[4]    * b.e[1] + e[5]     * b.e[5] + e[6]     * b.e[9]        + e[7]  * b.e[13], 
            e[4]    * b.e[2] + e[5]     * b.e[6] + e[6]     * b.e[10]       + e[7]  * b.e[14], 
            e[4]    * b.e[3] + e[5]     * b.e[7] + e[6]     * b.e[11]       + e[7]  * b.e[15], 
            e[8]    * b.e[0] + e[9]     * b.e[4] + e[10]    * b.e[8]        + e[11] * b.e[12], 
            e[8]    * b.e[1] + e[9]     * b.e[5] + e[10]    * b.e[9]        + e[11] * b.e[13], 
            e[8]    * b.e[2] + e[9]     * b.e[6] + e[10]    * b.e[10]       + e[11] * b.e[14], 
            e[8]    * b.e[3] + e[9]     * b.e[7] + e[10]    * b.e[11]       + e[11] * b.e[15], 
            e[12]   * b.e[0] + e[13]    * b.e[4] + e[14]    * b.e[8]        + e[15] * b.e[12], 
            e[12]   * b.e[1] + e[13]    * b.e[5] + e[14]    * b.e[9]        + e[15] * b.e[13], 
            e[12]   * b.e[2] + e[13]    * b.e[6] + e[14]    * b.e[10]       + e[15] * b.e[14], 
            e[12]   * b.e[3] + e[13]    * b.e[7] + e[14]    * b.e[11]       + e[15] * b.e[15]
        }};
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator*(const f32& value) const {
        Matrix<f32, 4, 4> mat = *this;

        for(f32& i : mat.e)
            i *= value;

        return mat;
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator/(const f32& value) const {
        Matrix<f32, 4, 4> mat = *this;

        for(f32& i : mat.e)
            i /= value;

        return mat;
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator+(const f32& value) const {
        Matrix<f32, 4, 4> mat = *this;

        for(f32& i : mat.e)
            i += value;

        return mat;
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::operator-(const f32& value) const {
        Matrix<f32, 4, 4> mat = *this;

        for(f32& i : mat.e)
            i -= value;

        return mat;
    }

    inline bool Matrix<f32, 4, 4>::operator==(const Matrix<f32, 4, 4>& other) const {
        for(size_t i = 0; i < 16; ++i) {
            if(e[i] != other.e[i]) {
                return false;
            }
        }

        return true;
    }

    inline bool Matrix<f32, 4, 4>::operator!=(const Matrix<f32, 4, 4>& other) const {
        return !(*this == other);
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::rotation_x(const f32& angle) {
        const f32 cos0 = std::cos(angle);
        const f32 sin0 = std::sin(angle);

        #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
        return {{
            1.0f, 0.0f,  0.0f, 0.0f,
            0.0f, cos0, -sin0, 0.0f,
            0.0f, sin0,  cos0, 0.0f,
            0.0f, 0.0f,  0.0f, 1.0f
        }};
        #else
        return {{
            1.0f,  0.0f,  0.0f, 0.0f,
            0.0f,  cos0,  sin0, 0.0f,
            0.0f, -sin0,  cos0, 0.0f,
            0.0f,  0.0f,  0.0f, 1.0f
        }};
        #endif
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::rotation_y(const f32& angle) {
        const f32 cos0 = std::cos(angle);
        const f32 sin0 = std::sin(angle);

        #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
        return {{
                cos0, 0.0f, sin0, 0.0f,
                0.0f, 1.0f, 0.0f, 0.0f,
            -sin0, 0.0f, cos0, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        }};
        #else
        return {{
                cos0, 0.0f, -sin0, 0.0f,
                0.0f, 1.0f,  0.0f, 0.0f,
                sin0, 0.0f,  cos0, 0.0f,
                0.0f, 0.0f,  0.0f, 1.0f
        }};
        #endif
    }

    inline Matrix<f32, 4, 4> Matrix<f32, 4, 4>::rotation_z(const f32& angle) {
        const f32 cos0 = std::cos(angle);
        const f32 sin0 = std::sin(angle);
        
        #ifndef BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
        return {{
            cos0, -sin0, 0.0f, 0.0f,
            sin0,  cos0, 0.0f, 0.0f,
            0.0f,  0.0f, 1.0f, 0.0f,
            0.0f,  0.0f, 0.0f, 1.0f
        }};
        #else
        return {{
                cos0, sin0, 0.0f, 0.0f,
            -sin0, cos0, 0.0f, 0.0f,
                0.0f, 0.0f, 1.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f
        }};
        #endif
    }
}

#endif
