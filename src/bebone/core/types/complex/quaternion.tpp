#ifndef _OMNI_TYPES_QUATERNION_TPP_
#define _OMNI_TYPES_QUATERNION_TPP_

#include "../primitive_types.h"

namespace bebone::core {
    struct Quaternion {
        f32 a, bi, cj, dk;
    
        inline Quaternion operator+(const Quaternion& quat) const;
        inline Quaternion operator-(const Quaternion& quat) const;
        inline Quaternion operator*(const Quaternion& quat) const;

        inline Quaternion& operator+=(const Quaternion& other);
        inline Quaternion& operator-=(const Quaternion& other);
        inline Quaternion& operator*=(const Quaternion& other);
        inline Quaternion& operator/=(const Quaternion& other);
    };
}   

namespace bebone::core {
    Quaternion Quaternion::operator+(const Quaternion& quat) const {
        return {
            this->a + quat.a,
            this->bi + quat.bi,
            this->cj + quat.cj,
            this->dk + quat.dk
        }; 
    }

    Quaternion Quaternion::operator-(const Quaternion& quat) const {
        return {
            this->a - quat.a,
            this->bi - quat.bi,
            this->cj - quat.cj,
            this->dk - quat.dk
        }; 
    }

    Quaternion Quaternion::operator*(const Quaternion& quat) const {
        const auto& w1 = this->a;
        const auto& x1 = this->bi;
        const auto& y1 = this->cj;
        const auto& z1 = this->dk;

        const auto& w2 = quat.a;
        const auto& x2 = quat.bi;
        const auto& y2 = quat.cj;
        const auto& z2 = quat.dk;

        return {
            w1*w2 - x1*x2 - y1*y2 - z1*z2,
            w1*x2 + x1*w2 + y1*z2 - z1*y2,
            w1*y2 - x1*z2 + y1*w2 + z1*x2,
            w1*z2 + x1*y2 - y1*x2 + z1*w2
        }; 
    }

    Quaternion& Quaternion::operator+=(const Quaternion& quat) {
        this->a += quat.a;
        this->bi += quat.bi;
        this->cj += quat.cj;
        this->dk += quat.dk;
        
        return *this;
    }

    Quaternion& Quaternion::operator-=(const Quaternion& quat) {
        this->a -= quat.a;
        this->bi -= quat.bi;
        this->cj -= quat.cj;
        this->dk -= quat.dk;

        return *this;
    }

    Quaternion& Quaternion::operator*=(const Quaternion& quat) {
        *this = *this * quat;
        
        return *this;
    }
}

#endif
