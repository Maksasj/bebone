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

        constexpr Vec4() {}
        constexpr Vec4(const T& x, const T& y, const T& z, const T& w) : x(x), y(y), z(z), w(w) {}

        static Vec4<T> splat(const T& value) {
            return Vec4(value, value, value, value);
        }

        static const Vec4<float> zero;
        static const Vec4<float> one;

        /** @brief Some overoaded operators */
        inline Vec4 operator+(const Vec4& vec) const;
        inline Vec4 operator-(const Vec4& vec) const;
        inline Vec4 operator*(const Vec4& vec) const;
        inline Vec4 operator/(const Vec4& vec) const;

        inline Vec4 operator+(const T& value) const;
        inline Vec4 operator-(const T& value) const;
        inline Vec4 operator*(const T& value) const;
        inline Vec4 operator/(const T& value) const;

        /* Vector x= Vector */
        inline Vec4<T>& operator+=(const Vec4<T>& other);
        inline Vec4<T>& operator-=(const Vec4<T>& other);
        inline Vec4<T>& operator*=(const Vec4<T>& other);
        inline Vec4<T>& operator/=(const Vec4<T>& other);

        /* Vector x= arbirary values */
        inline Vec4<T>& operator+=(const T& other);
        inline Vec4<T>& operator-=(const T& other);
        inline Vec4<T>& operator*=(const T& other);
        inline Vec4<T>& operator/=(const T& other);

        inline bool operator==(const Vec4<T>& other) const;
        inline bool operator!=(const Vec4<T>& other) const;

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

    /**
     * @brief Some overoaded operators
    */
    template<typename T>
    Vec4<T> Vec4<T>::operator+(const Vec4& vec) const { return Vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator-(const Vec4& vec) const { return Vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator*(const Vec4& vec) const { return Vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator/(const Vec4& vec) const { return Vec4(x / vec.x, y / vec.y, z / vec.z, w / vec.w); }

    template<typename T>
    Vec4<T> Vec4<T>::operator+(const T& value) const { return Vec4(x + value, y + value, z + value, w + value); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator-(const T& value) const { return Vec4( x - value, y - value, z - value, w - value); }

    template<typename T>
    Vec4<T> Vec4<T>::operator*(const T& value) const { return Vec4(x * value, y * value, z * value, w * value); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator/(const T& value) const { return Vec4( x / value, y / value, z / value, w / value); }

    /* Vector x= Vector */
    template<typename T>
    Vec4<T>& Vec4<T>::operator+=(const Vec4<T>& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator*=(const Vec4<T>& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator/=(const Vec4<T>& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

    /* Vector x= arbirary values */
    template<typename T>
    Vec4<T>& Vec4<T>::operator+=(const T& other) { x += other; y += other; z += other; w += other; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator-=(const T& other) { x -= other; y -= other; z -= other; w -= other; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator*=(const T& other) { x *= other; y *= other; z *= other; w *= other; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator/=(const T& other) { x /= other; y /= other; z /= other; w /= other; return *this; }


    template<typename T>
    bool Vec4<T>::operator==(const Vec4<T>& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
    
    template<typename T>
    bool Vec4<T>::operator!=(const Vec4<T>& other) const { return !(*this == other); }

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
     * @param vec - reference to the object instance
     * 
     * @return std::ostream& reference to the stream instance 
    */
    template<typename T>
    std::ostream& operator<<(std::ostream& os, const Vec4<T>& vec) {
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
    template<typename T>
    std::istream& operator>>(std::istream& os, const Vec4<T>& vec) {
        os >> vec.x >> vec.y >> vec.z >> vec.w;

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
        return length() == 1;
    }

}

#endif
