#ifndef _BEBONE_CORE_TYPES_VECTOR_4_TYPE_TPP_
#define _BEBONE_CORE_TYPES_VECTOR_4_TYPE_TPP_

#include "vector3_type.tpp"

namespace bebone::core {
    /**
     * @brief Type that used as 4d geometrical vector
     * 
     * @tparam T type of the vector
    */
    template<typename T>
    struct Vec4 {
        /** @brief Raw vector values */
        T x;
        T y;
        T z;
        T w;

        constexpr Vec4() = default;
        constexpr Vec4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

        static const Vec4<float> zero;
        static const Vec4<float> one;

        static Vec4<T> splat(const T& value);
        inline static T dot(const Vec4<T>& a, const Vec4<T>& b);
        inline static Vec4<T> project(const Vec4<T>& a, const Vec4<T>& b);
        inline static Vec4<T> reject(const Vec4<T>& a, const Vec4<T>& b);

        inline Vec4 operator +(const Vec4& v) const;
        inline Vec4 operator -(const Vec4& v) const;
        inline Vec4 operator *(const Vec4& v) const;
        inline Vec4 operator /(const Vec4& v) const;
        inline Vec4<T>& operator +=(const Vec4<T>& v);
        inline Vec4<T>& operator -=(const Vec4<T>& v);
        inline Vec4<T>& operator *=(const Vec4<T>& v);
        inline Vec4<T>& operator /=(const Vec4<T>& v);

        inline Vec4 operator +(const T& scalar) const;
        inline Vec4 operator -(const T& scalar) const;
        inline Vec4 operator *(const T& scalar) const;
        inline Vec4 operator /(T scalar) const;
        inline Vec4<T>& operator +=(const T& scalar);
        inline Vec4<T>& operator -=(const T& scalar);
        inline Vec4<T>& operator *=(const T& scalar);
        inline Vec4<T>& operator /=(T scalar);

        inline Vec4 operator -() const;

        inline bool operator ==(const Vec4<T>& v) const;
        inline bool operator !=(const Vec4<T>& v) const;

        inline explicit operator Vec2<T>() const;
        inline explicit operator Vec3<T>() const;

        inline std::string to_string() const;

        inline Vec4<T>& clamp(const T& min_value, const T& max_value);
        inline Vec4<T>& clamp(const Vec4<T>& min_value, const Vec4<T>& max_value);
        
        inline Vec4<T>& abs();
        inline f32 length() const;
        inline Vec4<T> normalize() const;

        inline bool is_normalized() const;
    };
}

namespace bebone::core {
    template<typename T>
    const Vec4<float> Vec4<T>::zero{ 0.0f, 0.0f, 0.0f, 0.0f };

    template<typename T>
    const Vec4<float> Vec4<T>::one{ 1.0f, 1.0f, 1.0f, 1.0f };

    template<typename T>
    Vec4<T> Vec4<T>::operator +(const Vec4& v) const { return Vec4(x + v.x, y + v.y, z + v.z, w + v.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator -(const Vec4& v) const { return Vec4(x - v.x, y - v.y, z - v.z, w - v.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator *(const Vec4& v) const { return Vec4(x * v.x, y * v.y, z * v.z, w * v.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator /(const Vec4& v) const { return Vec4(x / v.x, y / v.y, z / v.z, w / v.w); }

    template<typename T>
    Vec4<T>& Vec4<T>::operator +=(const Vec4<T>& v) { x += v.x; y += v.y; z += v.z; w += v.w; return *this; }

    template<typename T>
    Vec4<T>& Vec4<T>::operator -=(const Vec4<T>& v) { x -= v.x; y -= v.y; z -= v.z; w -= v.w; return *this; }

    template<typename T>
    Vec4<T>& Vec4<T>::operator *=(const Vec4<T>& v) { x *= v.x; y *= v.y; z *= v.z; w *= v.w; return *this; }

    template<typename T>
    Vec4<T>& Vec4<T>::operator /=(const Vec4<T>& v) { x /= v.x; y /= v.y; z /= v.z; w /= v.w; return *this; }

    template<typename T>
    Vec4<T> Vec4<T>::operator +(const T& scalar) const { return Vec4(x + scalar, y + scalar, z + scalar, w + scalar); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator -(const T& scalar) const { return Vec4(x - scalar, y - scalar, z - scalar, w - scalar); }

    template<typename T>
    Vec4<T> Vec4<T>::operator *(const T& scalar) const { return Vec4(x * scalar, y * scalar, z * scalar, w * scalar); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator /(T scalar) const {
        scalar = 1.0f / scalar;
        return *this * scalar;
    }

    template<typename T>
    Vec4<T>& Vec4<T>::operator +=(const T& scalar) { x += scalar; y += scalar; z += scalar; w += scalar; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator -=(const T& scalar) { x -= scalar; y -= scalar; z -= scalar; w -= scalar; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator *=(const T& scalar) { x *= scalar; y *= scalar; z *= scalar; w *= scalar; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator /=(T scalar) {
        scalar = 1.0f / scalar;
        return *this *= scalar;
    }

    template<typename T>
    Vec4<T> Vec4<T>::operator -() const { return Vec4(-x, -y, -z, -w); }

    template<typename T>
    bool Vec4<T>::operator ==(const Vec4<T>& v) const { return x == v.x && y == v.y && z == v.z && w == v.w; }
    
    template<typename T>
    bool Vec4<T>::operator !=(const Vec4<T>& v) const { return !(*this == v); }

    template<typename T>
    Vec4<T>::operator Vec2<T>() const { return Vec2(x, y); }

    template<typename T>
    Vec4<T>::operator Vec3<T>() const { return Vec3(x, y, z); }

    template<typename T>
    Vec4<T> Vec4<T>::splat(const T& value) { return Vec4(value, value, value, value); }

    template<typename T>
    T Vec4<T>::dot(const Vec4<T>& a, const Vec4<T>& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
    }

    template<typename T>
    Vec4<T> Vec4<T>::project(const Vec4<T>& a, const Vec4<T>& b) {
        return b * (dot(a, b) / dot(b, b));
    }

    template<typename T>
    Vec4<T> Vec4<T>::reject(const Vec4<T>& a, const Vec4<T>& b) {
        return a - project(a, b);
    }

    template<typename T>
    Vec4<T>& Vec4<T>::clamp(const T& min_value, const T& max_value) {
        x = bebone::core::clamp(x, min_value, max_value);
        y = bebone::core::clamp(y, min_value, max_value);
        z = bebone::core::clamp(z, min_value, max_value);
        w = bebone::core::clamp(w, min_value, max_value);

        return *this;
    }
    
    template<typename T>
    Vec4<T>& Vec4<T>::clamp(const Vec4<T>& min_value, const Vec4<T>& max_value) {
        x = bebone::core::clamp(x, min_value.x, max_value.x);
        y = bebone::core::clamp(y, min_value.y, max_value.y);
        z = bebone::core::clamp(z, min_value.z, max_value.z);
        w = bebone::core::clamp(w, min_value.w, max_value.w);

        return *this;
    }

    /**
     * @brief Puts string representation of the object to the out stream
     * 
     * @param os - reference to the out stream
     * @param v - reference to the object instance
     * 
     * @return std::ostream& reference to the stream instance 
    */
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vec4<T>& v) {
        os << v.x << " " << v.y << " " << v.z << " " << v.w; 
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
    std::istream& operator>>(std::istream& os, const Vec4<T>& v) {
        os >> v.x >> v.y >> v.z >> v.w;

        return os;
    } 

    /**
     * @brief Method used to get string representation of object instance
     * 
     * @return std::string string representation 
    */
    template<typename T>
    std::string Vec4<T>::to_string() const {
        std::stringstream ss;
        ss << x << ' ' << y << ' ' << z << ' ' << w;
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<T>& reference to vector instance
    */
    template<typename T>
    Vec4<T>& Vec4<T>::abs() {
        if(x < 0) x = -x;
        if(y < 0) y = -y;
        if(z < 0) z = -z;
        if(w < 0) z = -w;
        return *this;
    }

    /**
     * @brief Calculates length of the vector
     * 
     * @return f32 length of the vector
    */
    template<typename T>
    f32 Vec4<T>::length() const {
        return sqrtf(x * x + y * y + z * z + w * w);
    }

    template<typename T>
    Vec4<T> Vec4<T>::normalize() const {
        return *this / length();
    }

    template<typename T>
    bool Vec4<T>::is_normalized() const {
        return std::abs(1.0f - length()) < std::numeric_limits<float>::epsilon();
    }

}

#endif
