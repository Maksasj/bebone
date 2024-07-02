#ifndef _BEBONE_CORE_TYPES_PROPER_EULER_ANGLES_
#define _BEBONE_CORE_TYPES_PROPER_EULER_ANGLES_

#include "../matrix/matrix_4x4.tpp"

namespace bebone::core {
    static inline Matrix<f32, 4, 4> proper_euler_angle_xzx(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        return {{
            c2,     -c3*s2,             s2*s3,                  0.0f,
            c1*s2,  c1*c2*c3 - s1*s3,   -c3*s1 - c1*c2*s3,      0.0f,
            s1*s2,  c1*s3 + c2*c3*s1,   c1*c3 - c2*s1*s3,       0.0f,
            0.0f,   0.0f,               0.0f,                   1.0f
        }};
    }

    static inline Matrix<f32, 4, 4> proper_euler_angle_xyx(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        return {{
            c2,         s2*s3,              c3*s2,              0.0f,
            -s1*s2,     c1*c3 - c2*s1*s3,   -c1*s3 - c2*c3*s1,  0.0f,
            -c1*s2,     c3*s1 + c1*c2*s3,   c1*c2*c3 - s1*s3,   0.0f,
            0.0f,       0.0f,               0.0f,               1.0f
        }};
    }

    static inline Matrix<f32, 4, 4> proper_euler_angle_yxy(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        return {{
            c1*c3 - c2*s1*s3,   s1*s2,      c1*s3 + c2*c3*s1,   0.0f,
            s2*s3,              c2,         -c3*s2,             0.0f,
            -c3*s1 - c1*c2*s3,  c1*s2,      c1*c2*c3 - s1*s3,   0.0f,
            0.0f,               0.0f,       0.0f,               1.0f
        }};
    }

    static inline Matrix<f32, 4, 4> proper_euler_angle_yzy(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        return {{
            c1*c2*c3 - s1*s2,   -c1*s3,     c3*s1 + c1*c2*s3,   0.0f,
            c3*s2,              c2,         s2*s3,              0.0f,
            -c1*s3 - c2*c3*s1,  s1*s2,      c1*c3 - c2*s1*s3,   0.0f,
            0.0f,               0.0f,       0.0f,               1.0f
        }};
    }

    static inline Matrix<f32, 4, 4> proper_euler_angle_zyz(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        return {{
            c1*c2*c3 - s1*s3,   -c3*s1 - c1*c2*s3,  c1*s2,      0.0f,
            c1*s3 + c2*c3*s1,   c1*c3 - c2*s1*s3,   s1*s2,      0.0f,
            -c3*s2,             s2*s3,              c2,         0.0f,
            0.0f,               0.0f,               0.0f,       1.0f
        }};
    }

    static inline Matrix<f32, 4, 4> proper_euler_angle_zxz(const Vec3f& rotation) {
        const f32 c3 = std::cos(rotation.z);
        const f32 s3 = std::sin(rotation.z);
        const f32 c2 = std::cos(rotation.x);
        const f32 s2 = std::sin(rotation.x);
        const f32 c1 = std::cos(rotation.y);
        const f32 s1 = std::sin(rotation.y);

        return {{
            c1*c3 - c2*s1*s3,   -c1*s3 - c2*c3*s1,  s1*s2,      0.0f,
            c3*s1 + c1*c2*s3,   c1*c2*c3 - s1*s3,   -c1*s2,     0.0f,
            s2*s3,              c3*s2,              c2,         0.0f,
            0.0f,               0.0f,               0.0f,       1.0f
        }};
    }
}

#endif
