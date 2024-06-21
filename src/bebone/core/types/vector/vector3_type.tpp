#ifndef _BEBONE_CORE_TYPES_VECTOR_3_TYPE_TPP_
#define _BEBONE_CORE_TYPES_VECTOR_3_TYPE_TPP_

#include "vector2_type.tpp"

namespace bebone::core {
    /**
     * @brief Type that used as 3d geometrical vector
     * 
     * @tparam _T type of the vector
    */
    template<typename _T>
    struct Vec3 {
        /** @brief Raw vector values */
        _T x;
        _T y;
        _T z;

        constexpr Vec3() {}
        constexpr Vec3(const _T& _x, const _T& _y, const _T& _z) : x(_x), y(_y), z(_z) {}

        static const Vec3<float> zero;
        static const Vec3<float> one;

        static const Vec3<float> left;
        static const Vec3<float> right;
        static const Vec3<float> up;
        static const Vec3<float> down;
        static const Vec3<float> back;
        static const Vec3<float> forward;

        inline static Vec3<_T> splat(const _T& value) {
            return Vec3(value, value, value);
        }

        /** @brief Some overoaded operators */
        inline Vec3 operator+(const Vec3& vec) const;
        inline Vec3 operator-(const Vec3& vec) const;
        inline Vec3 operator*(const Vec3& vec) const;
        inline Vec3 operator/(const Vec3& vec) const;

        inline Vec3 operator+(const _T& value) const;
        inline Vec3 operator-(const _T& value) const;
        inline Vec3 operator*(const _T& value) const;
        inline Vec3 operator/(const _T& value) const;

        /* Vector x= Vector */
        inline Vec3<_T>& operator+=(const Vec3<_T>& other);
        inline Vec3<_T>& operator-=(const Vec3<_T>& other);
        inline Vec3<_T>& operator*=(const Vec3<_T>& other);
        inline Vec3<_T>& operator/=(const Vec3<_T>& other);
        
        /* Vector x= arbirary values */
        inline Vec3<_T>& operator+=(const _T& other);
        inline Vec3<_T>& operator-=(const _T& other);
        inline Vec3<_T>& operator*=(const _T& other);
        inline Vec3<_T>& operator/=(const _T& other);

        inline operator Vec2<_T>() const;

        inline bool operator==(const Vec3<_T>& other) const;
        inline bool operator!=(const Vec3<_T>& other) const;

        inline std::string to_string() const;

        inline Vec3<_T>& clamp(const _T& minValue, const _T& maxValue);
        inline Vec3<_T>& clamp(const Vec3<_T>& minValue, const Vec3<_T>& maxValue);

        inline Vec3<_T>& abs();
        inline _T length() const;
        
        inline Vec3<_T> normalize() const;
        inline Vec3<_T> cross(const Vec3<_T>& other) const;
        inline _T dot(const Vec3<_T>& other) const;
    };
}

namespace bebone::core {
    template<typename _T>
    const Vec3<float> Vec3<_T>::zero{ 0.0f, 0.0f, 0.0f };

    template<typename _T>
    const Vec3<float> Vec3<_T>::one{ 1.0f, 1.0f, 1.0f };

    template<typename _T>
    const Vec3<float> Vec3<_T>::left{ -1.0f, 0.0f, 0.0f };

    template<typename _T>
    const Vec3<float> Vec3<_T>::right{ 1.0f, 0.0f, 0.0f };

    template<typename _T>
    const Vec3<float> Vec3<_T>::up{ 0.0f, 1.0f, 0.0f };

    template<typename _T>
    const Vec3<float> Vec3<_T>::down{ 0.0f, -1.0f, 0.0f };

    template<typename _T>
    const Vec3<float> Vec3<_T>::back{ 0.0f, 0.0f, -1.0f };

    template<typename _T>
    const Vec3<float> Vec3<_T>::forward{ 0.0f, 0.0f, 1.0f };

    template<typename _T>
    Vec3<_T> Vec3<_T>::operator+(const Vec3& vec) const { return Vec3(this->x + vec.x, this->y + vec.y, z + vec.z); }
    
    template<typename _T>
    Vec3<_T> Vec3<_T>::operator-(const Vec3& vec) const { return Vec3(this->x - vec.x, this->y - vec.y, z - vec.z); }
    
    template<typename _T>
    Vec3<_T> Vec3<_T>::operator*(const Vec3& vec) const { return Vec3(this->x * vec.x, this->y * vec.y, z * vec.z); }
    
    template<typename _T>
    Vec3<_T> Vec3<_T>::operator/(const Vec3& vec) const { return Vec3(this->x / vec.x, this->y / vec.y, z / vec.z); }

    template<typename _T>
    Vec3<_T> Vec3<_T>::operator+(const _T& value) const { return Vec3(this->x + value, this->y + value, this->z + value); }
    
    template<typename _T>
    Vec3<_T> Vec3<_T>::operator-(const _T& value) const { return Vec3(this->x - value, this->y - value, this->z - value); }

    template<typename _T>
    Vec3<_T> Vec3<_T>::operator*(const _T& value) const { return Vec3(this->x * value, this->y * value, this->z * value); }
    
    template<typename _T>
    Vec3<_T> Vec3<_T>::operator/(const _T& value) const { return Vec3(this->x / value, this->y / value, this->z / value); }

    /* Vector x= Vector */
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator+=(const Vec3<_T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; return *this; }
    
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator-=(const Vec3<_T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; return *this; }
    
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator*=(const Vec3<_T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; return *this; }
    
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator/=(const Vec3<_T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; return *this; }
    
    /* Vector x= arbirary values */
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator+=(const _T& other) { this->x += other; this->y += other; this->z += other; return *this; }
    
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator-=(const _T& other) { this->x -= other; this->y -= other; this->z -= other; return *this; }
    
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator*=(const _T& other) { this->x *= other; this->y *= other; this->z *= other; return *this; }
    
    template<typename _T>
    Vec3<_T>& Vec3<_T>::operator/=(const _T& other) { this->x /= other; this->y /= other; this->z /= other; return *this; }

    template<typename _T>
    Vec3<_T>::operator Vec2<_T>() const { return Vec2<_T>{this->x, this->y}; }

    template<typename _T>
    bool Vec3<_T>::operator==(const Vec3<_T>& other) const { return this->x == other.x && this->y == other.y && this->z == other.z; }
    
    template<typename _T>
    bool Vec3<_T>::operator!=(const Vec3<_T>& other) const { return !(*this == other); }

    template<typename _T>
    Vec3<_T>& Vec3<_T>::clamp(const _T& minValue, const _T& maxValue) {
        this->x = bebone::core::clamp(this->x, minValue, maxValue);
        this->y = bebone::core::clamp(this->y, minValue, maxValue);
        this->z = bebone::core::clamp(this->z, minValue, maxValue);

        return *this;
    }
    
    template<typename _T>
    Vec3<_T>& Vec3<_T>::clamp(const Vec3<_T>& minValue, const Vec3<_T>& maxValue) {
        this->x = bebone::core::clamp(this->x, minValue.x, maxValue.x);
        this->y = bebone::core::clamp(this->y, minValue.y, maxValue.y);
        this->z = bebone::core::clamp(this->z, minValue.z, maxValue.z);

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
    std::ostream& operator<<(std::ostream& os, const Vec3<_T>& vec) {
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
    template<typename _T>
    std::istream& operator>>(std::istream& os, const Vec3<_T>& vec) {
        os >> vec.x >> vec.y >> vec.z;

        return os;
    } 

    /**
     * @brief Method used to get string representation of object instance
     * 
     * @return std::string string representation 
    */
    template<typename _T>
    std::string Vec3<_T>::to_string() const {
        std::stringstream ss;
        ss << this->x << ' ' << this->y << ' ' << z;
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<_T>& reference to vector instance
    */
    template<typename _T>
    Vec3<_T>& Vec3<_T>::abs() {
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
    template<typename _T>
    _T Vec3<_T>::length() const {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
    }

    template<typename _T>
    Vec3<_T> Vec3<_T>::normalize() const {
        const _T l = length();
        return Vec3<_T>(x / l, y / l, z / l);
    }

    template<typename _T>
    Vec3<_T> Vec3<_T>::cross(const Vec3<_T>& other) const {
        return Vec3<_T>(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
    
    template<typename _T>
    _T Vec3<_T>::dot(const Vec3<_T>& other) const {
        return x * other.x + y * other.y + z * other.z;
    }
}

#endif
