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

        constexpr Vec2() {}
        constexpr Vec2(const T& x, const T& y) : x(x), y(y) {}

        static const Vec2<float> zero;
        static const Vec2<float> one;

        static const Vec2<float> left;
        static const Vec2<float> right;
        static const Vec2<float> up;
        static const Vec2<float> down;

        inline static Vec2<T> splat(const T& value) {
            return Vec2(value, value);
        }

        /** @brief Some overoaded operators */
        inline Vec2 operator+(const Vec2& vec) const;
        inline Vec2 operator-(const Vec2& vec) const;
        inline Vec2 operator*(const Vec2& vec) const;
        inline Vec2 operator/(const Vec2& vec) const;

        inline Vec2 operator+(const T& value) const;
        inline Vec2 operator-(const T& value) const;
        inline Vec2 operator*(const T& value) const;
        inline Vec2 operator/(const T& value) const;

        /* Vector x= Vector */
        inline Vec2<T>& operator+=(const Vec2<T>& other);
        inline Vec2<T>& operator-=(const Vec2<T>& other);
        inline Vec2<T>& operator*=(const Vec2<T>& other);
        inline Vec2<T>& operator/=(const Vec2<T>& other);

        /* Vector x= arbirary values */
        inline Vec2<T>& operator+=(const T& other);
        inline Vec2<T>& operator-=(const T& other);
        inline Vec2<T>& operator*=(const T& other);
        inline Vec2<T>& operator/=(const T& other);

        inline bool operator==(const Vec2<T>& other) const;
        inline bool operator!=(const Vec2<T>& other) const;

        inline std::string to_string() const;

        inline Vec2<T>& clamp(const T& min_value, const T& max_value);
        inline Vec2<T>& clamp(const Vec2<T>& min_value, const Vec2<T>& max_value);
        
        inline Vec2<T>& abs();
        inline T length() const;
        inline Vec2<T> normalize() const;

        inline T dot(const Vec2<T>& other) const;
        inline Vec2<T> project(const Vec2<T>& other) const;
        inline Vec2<T> reject(const Vec2<T>& other) const;
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
    Vec2<T> Vec2<T>::operator+(const Vec2& vec) const { return Vec2(x + vec.x, y + vec.y); }

    template<typename T>
    Vec2<T> Vec2<T>::operator-(const Vec2& vec) const { return Vec2(x - vec.x, y - vec.y); }

    template<typename T>
    Vec2<T> Vec2<T>::operator*(const Vec2& vec) const { return Vec2(x * vec.x, y * vec.y); }

    template<typename T>
    Vec2<T> Vec2<T>::operator/(const Vec2& vec) const { return Vec2(x / vec.x, y / vec.y); }

    template<typename T>
    Vec2<T> Vec2<T>::operator+(const T& value) const { return Vec2(x + value, y + value); }
    
    template<typename T>
    Vec2<T> Vec2<T>::operator-(const T& value) const { return Vec2(x - value, y - value); }

    template<typename T>
    Vec2<T> Vec2<T>::operator*(const T& value) const { return Vec2(x * value, y * value); }
    
    template<typename T>
    Vec2<T> Vec2<T>::operator/(const T& value) const { return Vec2(x / value, y / value); }

    /* Vector x= Vector */
    template<typename T>
    Vec2<T>& Vec2<T>::operator+=(const Vec2<T>& other) { this->x += other.x; this->y += other.y; return *this; }

    template<typename T>
    Vec2<T>& Vec2<T>::operator-=(const Vec2<T>& other) { this->x -= other.x; this->y -= other.y; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator*=(const Vec2<T>& other) { this->x *= other.x; this->y *= other.y; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator/=(const Vec2<T>& other) { this->x /= other.x; this->y /= other.y; return *this; }

    /* Vector x= arbirary values */
    template<typename T>
    Vec2<T>& Vec2<T>::operator+=(const T& other) { this->x += other; this->y += other; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator-=(const T& other) { this->x -= other; this->y -= other; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator*=(const T& other) { this->x *= other; this->y *= other; return *this; }
    
    template<typename T>
    Vec2<T>& Vec2<T>::operator/=(const T& other) { this->x /= other; this->y /= other; return *this; }

    template<typename T>
    bool Vec2<T>::operator==(const Vec2<T>& other) const { return this->x == other.x && this->y == other.y; }
    
    template<typename T>
    bool Vec2<T>::operator!=(const Vec2<T>& other) const { return !(*this == other); }

    template<typename T>
    Vec2<T>& Vec2<T>::clamp(const T& min_value, const T& max_value) {
        this->x = bebone::core::clamp(this->x, min_value, max_value);
        this->y = bebone::core::clamp(this->y, min_value, max_value);

        return *this;
    }
    
    template<typename T>
    Vec2<T>& Vec2<T>::clamp(const Vec2<T>& min_value, const Vec2<T>& max_value) {
        this->x = bebone::core::clamp(this->x, min_value.x, max_value.x);
        this->y = bebone::core::clamp(this->y, min_value.y, max_value.y);

        return *this;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vec2<T>& vec) {
        os << vec.x << " " << vec.y;
        return os;
    }

    template<typename T>
    std::istream& operator>>(std::istream& os, const Vec2<T>& vec) {
        os >> vec.x >> vec.y;
        return os;
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
        if(this->x < 0) this->x = -this->x;
        if(this->y < 0) this->y = -this->y;
        return *this;
    }

    /**
     * @brief Calculates length of the vector
     * 
     * @return T length of the vector
    */
    template<typename T>
    T Vec2<T>::length() const {
        return sqrtf(this->x * this->x + this->y * this->y);
    }

    template<typename T>
    Vec2<T> Vec2<T>::normalize() const {
        return *this / length();
    }

    template<typename T>
    T Vec2<T>::dot(const Vec2<T>& other) const {
        return x * other.x + y * other.y;
    }

    template<typename T>
    Vec2<T> Vec2<T>::project(const Vec2<T>& other) const {
        return other * (dot(other) / other.dot(other));
    }

    template<typename T>
    Vec2<T> Vec2<T>::reject(const Vec2<T>& other) const {
        return *this - project(other);
    }
}

#endif
