/**
 * @file 
 * vector4_type.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_VECTOR_4_TYPE_TPP_
#define _OMNI_TYPES_VECTOR_4_TYPE_TPP_

#include "vector3_type.tpp"

namespace omni::types {
    /**
     * @brief Type that used as 4d geometrical vector
     * 
     * @tparam _T type of the vector
    */
    template<typename _T>
    struct Vec4 {
        /** @brief Raw vector values */
        _T x;
        _T y;
        _T z;
        _T w;

        constexpr Vec4() {}
        constexpr Vec4(const _T& _x, const _T& _y, const _T& _z, const _T& _w) : x(_x), y(_y), z(_z), w(_w) {}

        static Vec4<_T> splat(const _T& value) {
            return Vec4(value, value, value, value);
        }

        static const Vec4<float> zero;
        static const Vec4<float> one;

        /** @brief Some overoaded operators */
        inline Vec4 operator+(const Vec4& vec) const;
        inline Vec4 operator-(const Vec4& vec) const;
        inline Vec4 operator*(const Vec4& vec) const;
        inline Vec4 operator/(const Vec4& vec) const;

        inline Vec4 operator+(const _T& value) const;
        inline Vec4 operator-(const _T& value) const;
        inline Vec4 operator*(const _T& value) const;
        inline Vec4 operator/(const _T& value) const;

        /* Vector x= Vector */
        inline Vec4<_T>& operator+=(const Vec4<_T>& other);
        inline Vec4<_T>& operator-=(const Vec4<_T>& other);
        inline Vec4<_T>& operator*=(const Vec4<_T>& other);
        inline Vec4<_T>& operator/=(const Vec4<_T>& other);

        /* Vector x= arbirary values */
        inline Vec4<_T>& operator+=(const _T& other);
        inline Vec4<_T>& operator-=(const _T& other);
        inline Vec4<_T>& operator*=(const _T& other);
        inline Vec4<_T>& operator/=(const _T& other);

        inline bool operator==(const Vec4<_T>& other) const;
        inline bool operator!=(const Vec4<_T>& other) const;

        inline std::string to_string() const;

        inline Vec4<_T>& clamp(const _T& minValue, const _T& maxValue);
        inline Vec4<_T>& clamp(const Vec4<_T>& minValue, const Vec4<_T>& maxValue);
        
        inline Vec4<_T>& abs();
        inline f32 length() const;
    };
}

namespace omni::types {
    template<typename _T>
    const Vec4<float> Vec4<_T>::zero{ 0.0f, 0.0f, 0.0f, 0.0f };

    template<typename _T>
    const Vec4<float> Vec4<_T>::one{ 1.0f, 1.0f, 1.0f, 1.0f };

    /**
     * @brief Some overoaded operators
    */
    template<typename _T>
    Vec4<_T> Vec4<_T>::operator+(const Vec4& vec) const { return Vec4(this->x + vec.x, this->y + vec.y, this->z + vec.z, w + vec.w); }
    
    template<typename _T>
    Vec4<_T> Vec4<_T>::operator-(const Vec4& vec) const { return Vec4(this->x - vec.x, this->y - vec.y, this->z - vec.z, w - vec.w); }
    
    template<typename _T>
    Vec4<_T> Vec4<_T>::operator*(const Vec4& vec) const { return Vec4(this->x * vec.x, this->y * vec.y, this->z * vec.z, w * vec.w); }
    
    template<typename _T>
    Vec4<_T> Vec4<_T>::operator/(const Vec4& vec) const { return Vec4(this->x / vec.x, this->y / vec.y, this->z / vec.z, w / vec.w); }

    template<typename _T>
    Vec4<_T> Vec4<_T>::operator+(const _T& value) const { return Vec4(this->x + value, this->y + value, this->z + value, this->w + value); }
    
    template<typename _T>
    Vec4<_T> Vec4<_T>::operator-(const _T& value) const { return Vec4( this->x - value, this->y - value, this->z - value, this->w - value); }

    template<typename _T>
    Vec4<_T> Vec4<_T>::operator*(const _T& value) const { return Vec4(this->x * value, this->y * value, this->z * value, this->w * value); }
    
    template<typename _T>
    Vec4<_T> Vec4<_T>::operator/(const _T& value) const { return Vec4( this->x / value, this->y / value, this->z / value, this->w / value); }

    /* Vector x= Vector */
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator+=(const Vec4<_T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; this->w += other.w; return *this; }
    
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator-=(const Vec4<_T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; this->w -= other.w; return *this; }
    
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator*=(const Vec4<_T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; this->w *= other.w; return *this; }
    
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator/=(const Vec4<_T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; this->w /= other.w; return *this; }

    /* Vector x= arbirary values */
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator+=(const _T& other) { this->x += other; this->y += other; this->z += other; this->w += other; return *this; }
    
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator-=(const _T& other) { this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this; }
    
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator*=(const _T& other) { this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this; }
    
    template<typename _T>
    Vec4<_T>& Vec4<_T>::operator/=(const _T& other) { this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this; }


    template<typename _T>
    bool Vec4<_T>::operator==(const Vec4<_T>& other) const { return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w; }
    
    template<typename _T>
    bool Vec4<_T>::operator!=(const Vec4<_T>& other) const { return !(*this == other); }

    template<typename _T>
    Vec4<_T>& Vec4<_T>::clamp(const _T& minValue, const _T& maxValue) {
        this->x = omni::types::clamp(this->x, minValue, maxValue);
        this->y = omni::types::clamp(this->y, minValue, maxValue);
        this->z = omni::types::clamp(this->z, minValue, maxValue);
        this->w = omni::types::clamp(this->w, minValue, maxValue);

        return *this;
    }
    
    template<typename _T>
    Vec4<_T>& Vec4<_T>::clamp(const Vec4<_T>& minValue, const Vec4<_T>& maxValue) {
        this->x = omni::types::clamp(this->x, minValue.x, maxValue.x);
        this->y = omni::types::clamp(this->y, minValue.y, maxValue.y);
        this->z = omni::types::clamp(this->z, minValue.z, maxValue.z);
        this->w = omni::types::clamp(this->w, minValue.w, maxValue.w);

        return *this;
    }

    /**
     * @brief Puts string representation of the object to the out stream
     * 
     * @param os - reference to the out stream
     * @param vec - reference to the object instance
     * 
     * @return std::ostream& reference to the stream instance 
    */
    template<typename _T>
    std::ostream& operator<<(std::ostream& os, const Vec4<_T>& vec) {
        os << vec.x << " " << vec.y << " " << vec.z << " " << vec.w; 
        return os;
    } 

    /**
     * @brief Constructs object from it string representation
     * 
     * @param os - reference to the in stream
     * @param vec - reference to the object instance
     * 
     * @return std::istream& reference to the stream instance 
    */
    template<typename _T>
    std::istream& operator>>(std::istream& os, const Vec4<_T>& vec) {
        os >> vec.x >> vec.y >> vec.z >> vec.w;

        return os;
    } 

    /**
     * @brief Method used to get string representation of object instance
     * 
     * @return std::string string representation 
    */
    template<typename _T>
    std::string Vec4<_T>::to_string() const {
        std::stringstream ss;
        ss << this->x << ' ' << this->y << ' ' << this->z << ' ' << w; 
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<_T>& reference to vector instance
    */
    template<typename _T>
    Vec4<_T>& Vec4<_T>::abs() {
        if(this->x < 0) this->x = -this->x;
        if(this->y < 0) this->y = -this->y;
        if(this->z < 0) this->z = -this->z;
        if(this->w < 0) this->z = -this->w;
        return *this;
    }

    /**
     * @brief Calculates length of the vector
     * 
     * @return f32 length of the vector
    */
    template<typename _T>
    f32 Vec4<_T>::length() const {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z,  + this->w * this->w);
    }
}

#endif
