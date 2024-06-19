/**
 * @file 
 * trait_bryan_angles.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_TRAIT_BRYAN_ANGLES_
#define _OMNI_TYPES_TRAIT_BRYAN_ANGLES_

#include "../matrix/matrix_4x4.tpp"

namespace bebone::core {
    static inline Matrix<f32, 4, 4> trait_bryan_angle_xzy(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        #ifndef OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
                return {{
                    c2*c3,              -s2,    c2*s3,                  0.0f,
                    s1*s3 + c1*c3*s2,   c1*c2,  c1*s2*s3 - c3*s1,       0.0f,
                    c3*s1*s2 - c1*s3,   c2*s1,  c1*c3 + s1*s2*s3,       0.0f,
                    0.0f,               0.0f,   0.0f,                   1.0f
                }};
        #else
                return {{
                    c2*c3,      s1*s3 + c1*c3*s2,    c3*s1*s2 - c1*s3,  0.0f,
                    -s2,        c1*c2,               c2*s1,             0.0f,
                    c2*s3 ,     c1*s2*s3 - c3*s1,    c1*c3 + s1*s2*s3,  0.0f,
                    0.0f,       0.0f,                0.0f,              1.0f
                }};
        #endif
    }

    static inline Matrix<f32, 4, 4> trait_bryan_angle_xyz(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        #ifndef OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
                return {{
                    c2*c3,              -c2*s3,             s2,         0.0f,
                    c1*s3 + c3*s1*s2,   c1*c3 - s1*s2*s3,   -c2*s1,     0.0f,
                    c1*s2*s3 - c3*s1,   c3*s1 + c1*s2*s3,   c1*c2,      0.0f,
                    0.0f,               0.0f,               0.0f,       1.0f
                }};
        #else
                return {{
                    c2*c3,      c1*s3 + c3*s1*s2,   c1*s2*s3 - c3*s1,   0.0f,
                    -c2*s3,     c1*c3 - s1*s2*s3,   c3*s1 + c1*s2*s3,   0.0f,
                    s2,         -c2*s1,             c1*c2,              0.0f,
                    0.0f,       0.0f,               0.0f,               1.0f
                }};
        #endif
    }

    static inline Matrix<f32, 4, 4> trait_bryan_angle_yxz(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        #ifndef OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
                return {{
                    c1*c3 + s1*s2*s3,   c3*s1*s2 - c1*s3,   c2*s1,      0.0f,
                    c2*s3,              c2*c3,              -s2,        0.0f,
                    c1*s2*s3-c3*s1,     c1*c3*s2 + s1*s3,   c1*c2,      0.0f,
                    0.0f,               0.0f,               0.0f,       1.0f
                }};
        #else
                return {{
                    c1*c3 + s1*s2*s3,   c2*s3,   c1*s2*s3-c3*s1,        0.0f,
                    c3*s1*s2 - c1*s3,   c2*c3,   c1*c3*s2 + s1*s3 ,     0.0f,
                    c2*s1,              -s2,     c1*c2,                 0.0f,
                    0.0f,               0.0f,    0.0f,                  1.0f
                }};
        #endif
    }

    static inline Matrix<f32, 4, 4> trait_bryan_angle_yzx(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        #ifndef OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
                return {{
                    c1*c2,      s1*s3 - c1*c3*c2,   c3*s1 + c1*s2*s3,   0.0f,
                    s2,         c2*c3,               -c2*s3,             0.0f,
                    -c2*s1,     c1*s3 + c3*s1*s2,   c1*c3 - s1*s2*s3,   0.0f,
                    0.0f,       0.0f,               0.0f,               1.0f
                }};
        #else
                return {{
                        c1*c2,              s2,         -c2*s1,             0.0f,
                        s1*s3 - c1*c3*c2,   c2*c3,       c1*s3 + c3*s1*s2,   0.0f,
                        c3*s1 + c1*s2*s3,   -c2*s3,     c1*c3 - s1*s2*s3,   0.0f,
                        0.0f,       0.0f,               0.0f,               1.0f
                }};
        #endif
    }

    static inline Matrix<f32, 4, 4> trait_bryan_angle_zyx(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        #ifndef OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
                return {{
                    c1*c2,      c1*s2*s3 - c3*s1,   s1*s3 + c1*c3*s2,   0.0f,
                    c2*s1,      c1*c3 + s1*s2*s3,   c3*s1*s2 - c1*s3,   0.0f,
                    -s2,        c2*s3,              c2*c3,              0.0f,
                    0.0f,       0.0f,               0.0f,               1.0f
                }};
        #else
                return {{
                        c1*c2,              c2*s1,              -s2,        0.0f,
                        c1*s2*s3 - c3*s1,   c1*c3 + s1*s2*s3,   c2*s3,      0.0f,
                        s1*s3 + c1*c3*s2,   c3*s1*s2 - c1*s3,   c2*c3,      0.0f,
                        0.0f,               0.0f,               0.0f,       1.0f
                }};
        #endif
    }

    static inline Matrix<f32, 4, 4> trait_bryan_angle_zxy(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        #ifndef OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
                return {{
                    c1*c3 - s1*s2*s3,   -c2*s1,     c1*s3 + c3*s1*s2,   0.0f,
                    c3*s1 + c1*s2*s3,   c1*c2,      s1*s3 - c1*c3*s2,   0.0f,
                    -c2*s3,             s2,         c2*c3,              0.0f,
                    0.0f,               0.0f,       0.0f,               1.0f
                }};
        #else
                return {{
                        c1*c3 - s1*s2*s3,   c3*s1 + c1*s2*s3,   -c2*s3,     0.0f,
                        -c2*s1,             c1*c2,              s2,         0.0f,
                        c1*s3 + c3*s1*s2,   s1*s3 - c1*c3*s2,   c2*c3,      0.0f,
                        0.0f,               0.0f,       0.0f,               1.0f
                }};
        #endif
    }
}

#endif
