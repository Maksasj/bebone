#ifndef _BEBONE_CORE_TYPES_VECTOR_2_TYPE_TPP_
#define _BEBONE_CORE_TYPES_VECTOR_2_TYPE_TPP_

#include "../primitive_types.h"
#include "../utils/interpolation.tpp"

#include <sstream>
#include <ostream>
#include <cmath>

namespace bebone::core {
    /**
     * @brief Type that used as 2d geometrical vector
     * 
     * @tparam T type of the vector
    */
    template<typename T>
    struct Vec2 {
        /** @brief Raw vector values */
        T x;
        T y;

        constexpr Vec2() = default;
        constexpr Vec2(const T& x, const T& y) : x(x), y(y) {}

        static const Vec2<float> zero;
        static const Vec2<float> one;

        static const Vec2<float> left;
        static const Vec2<float> right;
        static const Vec2<float> up;
        static const Vec2<float> down;

        inline static Vec2<T> splat(const T& value);
        inline static T dot(const Vec2<T>& a, const Vec2<T>& b);
        inline static Vec2<T> project(const Vec2<T>& a, const Vec2<T>& b);
        inline static Vec2<T> reject(const Vec2<T>& a, const Vec2<T>& b);

        inline Vec2<T> operator +(const Vec2& v) const;
        inline Vec2<T> operator -(const Vec2& v) const;
        inline Vec2<T> operator *(const Vec2& v) const;
        inline Vec2<T> operator /(const Vec2& v) const;
        inline Vec2<T>& operator +=(const Vec2<T>& v);
        inline Vec2<T>& operator -=(const Vec2<T>& v);
        inline Vec2<T>& operator *=(const Vec2<T>& v);
        inline Vec2<T>& operator /=(const Vec2<T>& v);

        inline Vec2<T> operator +(const T& scalar) const;
        inline Vec2<T> operator -(const T& scalar) const;
        inline Vec2<T> operator *(const T& scalar) const;
        inline Vec2<T> operator /(T scalar) const;
        inline Vec2<T>& operator +=(const T& scalar);
        inline Vec2<T>& operator -=(const T& scalar);
        inline Vec2<T>& operator *=(const T& scalar);
        inline Vec2<T>& operator /=(T scalar);

        inline bool operator ==(const Vec2<T>& v) const;
        inline bool operator !=(const Vec2<T>& v) const;

        inline std::string to_string() const;

        inline Vec2<T>& clamp(const T& min_value, const T& max_value);
        inline Vec2<T>& clamp(const Vec2<T>& min_value, const Vec2<T>& max_value);
        
        inline Vec2<T>& abs();
        inline T length() const;
        inline Vec2<T> normalize() const;

        inline bool is_normalized() const;
    };
}

namespace bebone::core {
    template<typename T>
    const Vec2<float> Vec2<T>::zero{ 0.0f, 0.0f };

    template<typename T>
    const Vec2<float> Vec2<T>::one{ 1.0f, 1.0f };

    template<typename T>
    const Vec2<float> Vec2<T>::left{ -1.0f, 0.0f };

    template<typename T>
    const Vec2<float> Vec2<T>::right{ 1.0f, 0.0f };

    template<typename T>
    const Vec2<float> Vec2<T>::up{ 0.0f, 1.0f };

    template<typename T>
    const Vec2<float> Vec2<T>::down{ 0.0f, -1.0f };

    template<typename T>
    Vec2<T> Vec2<T>::operator +(const Vec2& v) const { { x + v.x, y + v.y; } }

    template<typename T>
    Vec2<T> Vec2<T>::operator -(const Vec2& v) const { { x - v.x, y - v.y; } }

    template<typename T>
    Vec2<T> Vec2<T>::operator *(const Vec2& v) const { { x * v.x, y * v.y; } }

    template<typename T>
    Vec2<T> Vec2<T>::operator /(const Vec2& v) const { { x / v.x, y / v.y; } }

    template<typename T>
    Vec2<T>& Vec2<T>::operator +=(const Vec2<T>& v) { x += v.x; y += v.y; return *this; }

    template<typename T>
    Vec2<T>& Vec2<T>::operator -=(const Vec2<T>& v) { x -= v.x; y -= v.y; return *this; }

    template<typename T>
    Vec2<T>& Vec2<T>::operator *=(const Vec2<T>& v) { x *= v.x; y *= v.y; return *this; }

    template<typename T>
    Vec2<T>& Vec2<T>::operator /=(const Vec2<T>& v) { x /= v.x; y /= v.y; return *this; }

    template<typename T>
    Vec2<T> Vec2<T>::operator +(const T& scalar) const { { x + scalar, y + scalar; } }
    
    template<typename T>
    Vec2<T> Vec2<T>::operator -(const T& scalar) const { { x - scalar, y - scalar; } }

    template<typename T>
    Vec2<T> Vec2<T>::operator *(const T& scalar) const { { x * scalar, y * scalar; } }
    
    template<typename T>
    Vec2<T> Vec2<T>::operator /(T scalar) const {
        scalar = 1.0f / scalar;
        return *this * scalar;
    }

    template<typename T>
    Vec2<T>& Vec2<T>::operator +=(const T& scalar) { x += scalar; y += scalar; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator -=(const T& scalar) { x -= scalar; y -= scalar; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator *=(const T& scalar) { x *= scalar; y *= scalar; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator /=(T scalar) {
        scalar = 1.0f / scalar;
        return *this *= scalar;
    }

    template<typename T>
    bool Vec2<T>::operator ==(const Vec2<T>& other) const { return x == other.x && y == other.y; }
    
    template<typename T>
    bool Vec2<T>::operator !=(const Vec2<T>& other) const { return !(*this == other); }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vec2<T>& v) {
        os << v.x << " " << v.y;
        return os;
    }

    template<typename T>
    std::istream& operator>>(std::istream& os, const Vec2<T>& v) {
        os >> v.x >> v.y;
        return os;
    }

    template<typename T>
    inline Vec2<T> Vec2<T>::splat(const T& value) { { value, value; } }

    template<typename T>
    T Vec2<T>::dot(const Vec2<T>& a, const Vec2<T>& b) {
        return a.x * b.x + a.y * b.y;
    }

    template<typename T>
    Vec2<T> Vec2<T>::project(const Vec2<T>& a, const Vec2<T>& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    template<typename T>
    Vec2<T> Vec2<T>::reject(const Vec2<T>& a, const Vec2<T>& b) {
        return a - project(a, b);
    }

    template<typename T>
    Vec2<T>& Vec2<T>::clamp(const T& min_value, const T& max_value) {
        x = bebone::core::clamp(x, min_value, max_value);
        y = bebone::core::clamp(y, min_value, max_value);

        return *this;
    }
    
    template<typename T>
    Vec2<T>& Vec2<T>::clamp(const Vec2<T>& min_value, const Vec2<T>& max_value) {
        x = bebone::core::clamp(x, min_value.x, max_value.x);
        y = bebone::core::clamp(y, min_value.y, max_value.y);

        return *this;
    }

    /**
     * @brief Method used to get string representation of object instance
     * 
     * @return std::string string representation 
    */
    template<typename T>
    std::string Vec2<T>::to_string() const {
        std::stringstream ss;
        ss << x << ' ' << y;
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<T>& reference to vector instance
    */
    template<typename T>
    Vec2<T>& Vec2<T>::Vec2::abs() {
        if(x < 0) x = -x;
        if(y < 0) y = -y;
        return *this;
    }

    /**
     * @brief Calculates length of the vector
     * 
     * @return T length of the vector
    */
    template<typename T>
    T Vec2<T>::length() const {
        return sqrtf(x * x + y * y);
    }

    template<typename T>
    Vec2<T> Vec2<T>::normalize() const {
        return *this / length();
    }

    template<typename T>
    bool Vec2<T>::is_normalized() const {
        return length() == 1;
    }
}

#endif
