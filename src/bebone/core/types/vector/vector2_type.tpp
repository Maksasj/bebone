/**
 * @file 
 * vector2_type.tpp
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_VECTOR_2_TYPE_TPP_
#define _OMNI_TYPES_VECTOR_2_TYPE_TPP_

#include "../primitive_types.h"
#include "../utils/interpolation.tpp"

#include <sstream>
#include <ostream>
#include <cmath>

namespace bebone::core {
    /**
     * @brief Type that used as 2d geometrical vector
     * 
     * @tparam _T type of the vector
    */
    template<typename _T>
    struct Vec2 {
        /** @brief Raw vector values */
        _T x;
        _T y;

        constexpr Vec2() {}
        constexpr Vec2(const _T& _x, const _T& _y) : x(_x), y(_y) {}

        static const Vec2<float> zero;
        static const Vec2<float> one;

        static const Vec2<float> left;
        static const Vec2<float> right;
        static const Vec2<float> up;
        static const Vec2<float> down;

        inline static Vec2<_T> splat(const _T& value) {
            return Vec2(value, value);
        }

        /** @brief Some overoaded operators */
        inline Vec2 operator+(const Vec2& vec) const;
        inline Vec2 operator-(const Vec2& vec) const;
        inline Vec2 operator*(const Vec2& vec) const;
        inline Vec2 operator/(const Vec2& vec) const;

        inline Vec2 operator+(const _T& value) const;
        inline Vec2 operator-(const _T& value) const;
        inline Vec2 operator*(const _T& value) const;
        inline Vec2 operator/(const _T& value) const;

        /* Vector x= Vector */
        inline Vec2<_T>& operator+=(const Vec2<_T>& other);
        inline Vec2<_T>& operator-=(const Vec2<_T>& other);
        inline Vec2<_T>& operator*=(const Vec2<_T>& other);
        inline Vec2<_T>& operator/=(const Vec2<_T>& other);

        /* Vector x= arbirary values */
        inline Vec2<_T>& operator+=(const _T& other);
        inline Vec2<_T>& operator-=(const _T& other);
        inline Vec2<_T>& operator*=(const _T& other);
        inline Vec2<_T>& operator/=(const _T& other);

        inline bool operator==(const Vec2<_T>& other) const;
        inline bool operator!=(const Vec2<_T>& other) const;

        inline std::string to_string() const;

        inline Vec2<_T>& clamp(const _T& minValue, const _T& maxValue);
        inline Vec2<_T>& clamp(const Vec2<_T>& minValue, const Vec2<_T>& maxValue);
        
        inline Vec2<_T>& abs();
        inline _T length() const;
    };
}

namespace bebone::core {
    template<typename _T>
    const Vec2<float> Vec2<_T>::zero{ 0.0f, 0.0f };

    template<typename _T>
    const Vec2<float> Vec2<_T>::one{ 1.0f, 1.0f };

    template<typename _T>
    const Vec2<float> Vec2<_T>::left{ -1.0f, 0.0f };

    template<typename _T>
    const Vec2<float> Vec2<_T>::right{ 1.0f, 0.0f };

    template<typename _T>
    const Vec2<float> Vec2<_T>::up{ 0.0f, 1.0f };

    template<typename _T>
    const Vec2<float> Vec2<_T>::down{ 0.0f, -1.0f };

    template<typename _T>
    Vec2<_T> Vec2<_T>::operator+(const Vec2& vec) const { return Vec2(x + vec.x, y + vec.y); }

    template<typename _T>
    Vec2<_T> Vec2<_T>::operator-(const Vec2& vec) const { return Vec2(x - vec.x, y - vec.y); }

    template<typename _T>
    Vec2<_T> Vec2<_T>::operator*(const Vec2& vec) const { return Vec2(x * vec.x, y * vec.y); }

    template<typename _T>
    Vec2<_T> Vec2<_T>::operator/(const Vec2& vec) const { return Vec2(x / vec.x, y / vec.y); }

    template<typename _T>
    Vec2<_T> Vec2<_T>::operator+(const _T& value) const { return Vec2(x + value, y + value); }
    
    template<typename _T>
    Vec2<_T> Vec2<_T>::operator-(const _T& value) const { return Vec2(x - value, y - value); }

    template<typename _T>
    Vec2<_T> Vec2<_T>::operator*(const _T& value) const { return Vec2(x * value, y * value); }
    
    template<typename _T>
    Vec2<_T> Vec2<_T>::operator/(const _T& value) const { return Vec2(x / value, y / value); }

    /* Vector x= Vector */
    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator+=(const Vec2<_T>& other) { this->x += other.x; this->y += other.y; return *this; }

    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator-=(const Vec2<_T>& other) { this->x -= other.x; this->y -= other.y; return *this; }
    
    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator*=(const Vec2<_T>& other) { this->x *= other.x; this->y *= other.y; return *this; }
    
    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator/=(const Vec2<_T>& other) { this->x /= other.x; this->y /= other.y; return *this; }

    /* Vector x= arbirary values */
    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator+=(const _T& other) { this->x += other; this->y += other; return *this; }
    
    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator-=(const _T& other) { this->x -= other; this->y -= other; return *this; }
    
    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator*=(const _T& other) { this->x *= other; this->y *= other; return *this; }
    
    template<typename _T>
    Vec2<_T>& Vec2<_T>::operator/=(const _T& other) { this->x /= other; this->y /= other; return *this; }

    template<typename _T>
    bool Vec2<_T>::operator==(const Vec2<_T>& other) const { return this->x == other.x && this->y == other.y; }
    
    template<typename _T>
    bool Vec2<_T>::operator!=(const Vec2<_T>& other) const { return !(*this == other); }

    template<typename _T>
    Vec2<_T>& Vec2<_T>::clamp(const _T& minValue, const _T& maxValue) {
        this->x = bebone::core::clamp(this->x, minValue, maxValue);
        this->y = bebone::core::clamp(this->y, minValue, maxValue);

        return *this;
    }
    
    template<typename _T>
    Vec2<_T>& Vec2<_T>::clamp(const Vec2<_T>& minValue, const Vec2<_T>& maxValue) {
        this->x = bebone::core::clamp(this->x, minValue.x, maxValue.x);
        this->y = bebone::core::clamp(this->y, minValue.y, maxValue.y);

        return *this;
    }

    template<typename _T>
    std::ostream& operator<<(std::ostream& os, const Vec2<_T>& vec) {
        os << vec.x << " " << vec.y;
        return os;
    }

    template<typename _T>
    std::istream& operator>>(std::istream& os, const Vec2<_T>& vec) {
        os >> vec.x >> vec.y;
        return os;
    } 

    /**
     * @brief Method used to get string representation of object instance
     * 
     * @return std::string string representation 
    */
    template<typename _T>
    std::string Vec2<_T>::to_string() const {
        std::stringstream ss;
        ss << x << ' ' << y;
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<_T>& reference to vector instance
    */
    template<typename _T>
    Vec2<_T>& Vec2<_T>::Vec2::abs() {
        if(this->x < 0) this->x = -this->x;
        if(this->y < 0) this->y = -this->y;
        return *this;
    }

    /**
     * @brief Calculates length of the vector
     * 
     * @return _T length of the vector
    */
    template<typename _T>
    _T Vec2<_T>::length() const {
        return sqrtf(this->x * this->x + this->y * this->y);
    }
}

#endif
