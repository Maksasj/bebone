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

        constexpr Vec3() {}
        constexpr Vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

        static const Vec3<float> zero;
        static const Vec3<float> one;

        static const Vec3<float> left;
        static const Vec3<float> right;
        static const Vec3<float> up;
        static const Vec3<float> down;
        static const Vec3<float> back;
        static const Vec3<float> forward;

        inline static Vec3<T> splat(const T& value) {
            return Vec3(value, value, value);
        }

        /** @brief Some overoaded operators */
        inline Vec3 operator+(const Vec3& vec) const;
        inline Vec3 operator-(const Vec3& vec) const;
        inline Vec3 operator*(const Vec3& vec) const;
        inline Vec3 operator/(const Vec3& vec) const;

        inline Vec3 operator+(const T& value) const;
        inline Vec3 operator-(const T& value) const;
        inline Vec3 operator*(const T& value) const;
        inline Vec3 operator/(const T& value) const;

        /* Vector x= Vector */
        inline Vec3<T>& operator+=(const Vec3<T>& other);
        inline Vec3<T>& operator-=(const Vec3<T>& other);
        inline Vec3<T>& operator*=(const Vec3<T>& other);
        inline Vec3<T>& operator/=(const Vec3<T>& other);
        
        /* Vector x= arbirary values */
        inline Vec3<T>& operator+=(const T& other);
        inline Vec3<T>& operator-=(const T& other);
        inline Vec3<T>& operator*=(const T& other);
        inline Vec3<T>& operator/=(const T& other);

        inline operator Vec2<T>() const;

        inline bool operator==(const Vec3<T>& other) const;
        inline bool operator!=(const Vec3<T>& other) const;

        inline std::string to_string() const;

        inline Vec3<T>& clamp(const T& min_value, const T& max_value);
        inline Vec3<T>& clamp(const Vec3<T>& min_value, const Vec3<T>& max_value);

        inline Vec3<T>& abs();
        inline T length() const;

        inline Vec3<T> normalize() const;
        inline Vec3<T> cross(const Vec3<T>& other) const;
        inline T dot(const Vec3<T>& other) const;
        inline Vec3<T> project(const Vec3<T>& other) const;
        inline Vec3<T> reject(const Vec3<T>& other) const;
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
    Vec3<T> Vec3<T>::operator+(const Vec3& vec) const { return Vec3(this->x + vec.x, this->y + vec.y, z + vec.z); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator-(const Vec3& vec) const { return Vec3(this->x - vec.x, this->y - vec.y, z - vec.z); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator*(const Vec3& vec) const { return Vec3(this->x * vec.x, this->y * vec.y, z * vec.z); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator/(const Vec3& vec) const { return Vec3(this->x / vec.x, this->y / vec.y, z / vec.z); }

    template<typename T>
    Vec3<T> Vec3<T>::operator+(const T& value) const { return Vec3(this->x + value, this->y + value, this->z + value); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator-(const T& value) const { return Vec3(this->x - value, this->y - value, this->z - value); }

    template<typename T>
    Vec3<T> Vec3<T>::operator*(const T& value) const { return Vec3(this->x * value, this->y * value, this->z * value); }
    
    template<typename T>
    Vec3<T> Vec3<T>::operator/(const T& value) const { return Vec3(this->x / value, this->y / value, this->z / value); }

    /* Vector x= Vector */
    template<typename T>
    Vec3<T>& Vec3<T>::operator+=(const Vec3<T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator-=(const Vec3<T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator*=(const Vec3<T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator/=(const Vec3<T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }
    
    /* Vector x= arbirary values */
    template<typename T>
    Vec3<T>& Vec3<T>::operator+=(const T& other) { this->x += other; this->y += other; this->z += other; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator-=(const T& other) { this->x -= other; this->y -= other; this->z -= other; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator*=(const T& other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
    
    template<typename T>
    Vec3<T>& Vec3<T>::operator/=(const T& other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

    template<typename T>
    Vec3<T>::operator Vec2<T>() const { return Vec2<T>{this->x, this->y}; }

    template<typename T>
    bool Vec3<T>::operator==(const Vec3<T>& other) const { return this->x == other.x && this->y == other.y && this->z == other.z; }
    
    template<typename T>
    bool Vec3<T>::operator!=(const Vec3<T>& other) const { return !(*this == other); }

    template<typename T>
    Vec3<T>& Vec3<T>::clamp(const T& min_value, const T& max_value) {
        this->x = bebone::core::clamp(this->x, min_value, max_value);
        this->y = bebone::core::clamp(this->y, min_value, max_value);
        this->z = bebone::core::clamp(this->z, min_value, max_value);

        return *this;
    }
    
    template<typename T>
    Vec3<T>& Vec3<T>::clamp(const Vec3<T>& min_value, const Vec3<T>& max_value) {
        this->x = bebone::core::clamp(this->x, min_value.x, max_value.x);
        this->y = bebone::core::clamp(this->y, min_value.y, max_value.y);
        this->z = bebone::core::clamp(this->z, min_value.z, max_value.z);

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
    std::ostream& operator<<(std::ostream& os, const Vec3<T>& vec) {
        os << vec.x << " " << vec.y << " " << vec.z;
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
    std::istream& operator>>(std::istream& os, const Vec3<T>& vec) {
        os >> vec.x >> vec.y >> vec.z;

        return os;
    } 

    /**
     * @brief Method used to get string representation of object instance
     * 
     * @return std::string string representation 
    */
    template<typename T>
    std::string Vec3<T>::to_string() const {
        std::stringstream ss;
        ss << this->x << ' ' << this->y << ' ' << z;
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<T>& reference to vector instance
    */
    template<typename T>
    Vec3<T>& Vec3<T>::abs() {
        if(this->x < 0) this->x = -this->x;
        if(this->y < 0) this->y = -this->y;
        if(this->z < 0) this->z = -this->z;
        return *this;
    }

    /**
     * @brief Calculates length of the vector
     * 
     * @return f32 length of the vector
    */
    template<typename T>
    T Vec3<T>::length() const {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    template<typename T>
    Vec3<T> Vec3<T>::normalize() const {
        return *this / length();
    }

    template<typename T>
    Vec3<T> Vec3<T>::cross(const Vec3<T>& other) const {
        return Vec3<T>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    template<typename T>
    T Vec3<T>::dot(const Vec3<T>& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    template<typename T>
    Vec3<T> Vec3<T>::project(const Vec3<T>& other) const {
        return other * (dot(other) / other.dot(other));
    }

    template<typename T>
    Vec3<T> Vec3<T>::reject(const Vec3<T>& other) const {
        return *this - project(other);
    }
}

#endif
