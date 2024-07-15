#ifndef _BEBONE_CORE_TYPES_VECTOR_3_TYPE_TPP_
#define _BEBONE_CORE_TYPES_VECTOR_3_TYPE_TPP_

#include "vector2_type.tpp"

namespace bebone::core {
    /**
     * @brief Type that used as 3d geometrical vector
     * 
     * @tparam T type of the vector
    */
    template<typename T>
    struct Vec3 {
        /** @brief Raw vector values */
        T x;
        T y;
        T z;

        constexpr Vec3() = default;
        constexpr Vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) { }

        static const Vec3<float> zero;
        static const Vec3<float> one;

        static const Vec3<float> left;
        static const Vec3<float> right;
        static const Vec3<float> up;
        static const Vec3<float> down;
        static const Vec3<float> back;
        static const Vec3<float> forward;

        inline static Vec3<T> splat(const T& value);
        inline static Vec3<T> cross(const Vec3<T>& a, const Vec3<T>& b);
        inline static T dot(const Vec3<T>& a, const Vec3<T>& b);
        inline static Vec3<T> project(const Vec3<T>& a, const Vec3<T>& b);
        inline static Vec3<T> reject(const Vec3<T>& a, const Vec3<T>& b);

        inline Vec3 operator +(const Vec3<T>& v) const;
        inline Vec3 operator -(const Vec3<T>& v) const;
        inline Vec3 operator *(const Vec3<T>& v) const;
        inline Vec3 operator /(const Vec3<T>& v) const;
        inline Vec3<T>& operator +=(const Vec3<T>& v);
        inline Vec3<T>& operator -=(const Vec3<T>& v);
        inline Vec3<T>& operator *=(const Vec3<T>& v);
        inline Vec3<T>& operator /=(const Vec3<T>& v);

        inline Vec3 operator +(const T& scalar) const;
        inline Vec3 operator -(const T& scalar) const;
        inline Vec3 operator *(const T& scalar) const;
        inline Vec3 operator /(T scalar) const;
        inline Vec3<T>& operator +=(const T& scalar);
        inline Vec3<T>& operator -=(const T& scalar);
        inline Vec3<T>& operator *=(const T& scalar);
        inline Vec3<T>& operator /=(T scalar);

        inline Vec3 operator -() const;

        inline bool operator ==(const Vec3<T>& v) const;
        inline bool operator !=(const Vec3<T>& v) const;

        inline explicit operator Vec2<T>() const;

        inline std::string to_string() const;

        inline Vec3<T>& clamp(const T& min_value, const T& max_value);
        inline Vec3<T>& clamp(const Vec3<T>& min_value, const Vec3<T>& max_value);

        inline Vec3<T>& abs();
        inline T length() const;

        inline Vec3<T> normalize() const;
        inline bool is_normalized() const;
    };
}

namespace bebone::core {
    template<typename T>
    const Vec3<float> Vec3<T>::zero{ 0.0f, 0.0f, 0.0f };

    template<typename T>
    const Vec3<float> Vec3<T>::one{ 1.0f, 1.0f, 1.0f };

    template<typename T>
    const Vec3<float> Vec3<T>::left{ -1.0f, 0.0f, 0.0f };

    template<typename T>
    const Vec3<float> Vec3<T>::right{ 1.0f, 0.0f, 0.0f };

    template<typename T>
    const Vec3<float> Vec3<T>::up{ 0.0f, 1.0f, 0.0f };

    template<typename T>
    const Vec3<float> Vec3<T>::down{ 0.0f, -1.0f, 0.0f };

    template<typename T>
    const Vec3<float> Vec3<T>::back{ 0.0f, 0.0f, -1.0f };

    template<typename T>
    const Vec3<float> Vec3<T>::forward{ 0.0f, 0.0f, 1.0f };

    template<typename T>
    Vec3<T> Vec3<T>::operator +(const Vec3& v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator -(const Vec3& v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator *(const Vec3& v) const { return Vec3(x * v.x, y * v.y, z * v.z); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator /(const Vec3& v) const { return Vec3(x / v.x, y / v.y, z / v.z); }

    template<typename T>
    Vec3<T>& Vec3<T>::operator +=(const Vec3<T>& v) { x += v.x; y += v.y; z += v.z; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator -=(const Vec3<T>& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator *=(const Vec3<T>& v) { x *= v.x; y *= v.y; z *= v.z; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator /=(const Vec3<T>& v) { x /= v.x; y /= v.y; z /= v.z; return *this; }

    template<typename T>
    Vec3<T> Vec3<T>::operator +(const T& scalar) const { return Vec3(x + scalar, y + scalar, z + scalar); }

    template<typename T>
    Vec3<T> Vec3<T>::operator -(const T& scalar) const { return Vec3(x - scalar, y - scalar, z - scalar); }

    template<typename T>
    Vec3<T> Vec3<T>::operator *(const T& scalar) const { return Vec3(x * scalar, y * scalar, z * scalar); }

    template<typename T>
    Vec3<T> Vec3<T>::operator /(T scalar) const {
        scalar = 1.0f / scalar;
        return *this * scalar;
    }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator +=(const T& scalar) { x += scalar; y += scalar; z += scalar; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator -=(const T& scalar) { x -= scalar; y -= scalar; z -= scalar; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator *=(const T& scalar) { x *= scalar; y *= scalar; z *= scalar; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator /=(T scalar) {
        scalar = 1.0f / scalar;
        return *this *= scalar;
    }

    template<typename T>
    Vec3<T> Vec3<T>::operator -() const { return Vec3(-x, -y, -z); }

    template<typename T>
    Vec3<T>::operator Vec2<T>() const { return Vec2(x, y); }

    template<typename T>
    bool Vec3<T>::operator ==(const Vec3<T>& v) const { return x == v.x && y == v.y && z == v.z; }
    
    template<typename T>
    bool Vec3<T>::operator !=(const Vec3<T>& v) const { return !(*this == v); }

    /**
     * @brief Puts string representation of the object to the out stream
     *
     * @param os - reference to the out stream
     * @param v - reference to the object instance
     *
     * @return std::ostream& reference to the stream instance
    */
    template<typename T>
    std::ostream& operator <<(std::ostream& os, const Vec3<T>& v) {
        os << v.x << " " << v.y << " " << v.z;
        return os;
    }

    /**
     * @brief Constructs object from it string representation
     *
     * @param os - reference to the in stream
     * @param v - reference to the object instance
     *
     * @return std::istream& reference to the stream instance
    */
    template<typename T>
    std::istream& operator >>(std::istream& os, const Vec3<T>& v) {
        os >> v.x >> v.y >> v.z;

        return os;
    }

    template<typename T>
    Vec3<T>& Vec3<T>::clamp(const T& min_value, const T& max_value) {
        x = bebone::core::clamp(x, min_value, max_value);
        y = bebone::core::clamp(y, min_value, max_value);
        z = bebone::core::clamp(z, min_value, max_value);

        return *this;
    }
    
    template<typename T>
    Vec3<T>& Vec3<T>::clamp(const Vec3<T>& min_value, const Vec3<T>& max_value) {
        x = bebone::core::clamp(x, min_value.x, max_value.x);
        y = bebone::core::clamp(y, min_value.y, max_value.y);
        z = bebone::core::clamp(z, min_value.z, max_value.z);

        return *this;
    }

    template<typename T>
    Vec3<T> Vec3<T>::splat(const T& value) {
        return Vec3(value, value, value);
    }

    template<typename T>
    Vec3<T> Vec3<T>::cross(const Vec3<T>& a, const Vec3<T>& b) {
        return {
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        };
    }

    template<typename T>
    T Vec3<T>::dot(const Vec3<T>& a, const Vec3<T>& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    template<typename T>
    Vec3<T> Vec3<T>::project(const Vec3<T>& a, const Vec3<T>& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    template<typename T>
    Vec3<T> Vec3<T>::reject(const Vec3<T>& a, const Vec3<T>& b) {
        return a - project(a, b);
    }

    /**
     * @brief Method used to get string representation of object instance
     * 
     * @return std::string string representation 
    */
    template<typename T>
    std::string Vec3<T>::to_string() const {
        std::stringstream ss;
        ss << x << ' ' << y << ' ' << z;
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<T>& reference to vector instance
    */
    template<typename T>
    Vec3<T>& Vec3<T>::abs() {
        if(x < 0) x = -x;
        if(y < 0) y = -y;
        if(z < 0) z = -z;
        return *this;
    }

    /**
     * @brief Calculates length of the vector
     * 
     * @return f32 length of the vector
    */
    template<typename T>
    T Vec3<T>::length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    template<typename T>
    Vec3<T> Vec3<T>::normalize() const {
        return *this / length();
    }

    template<typename T>
    bool Vec3<T>::is_normalized() const {
        // TODO: FIX THIS
        return length() == 1;
    }
}

#endif
