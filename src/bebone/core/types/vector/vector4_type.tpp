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
    Vec4<T> Vec4<T>::operator+(const Vec4& vec) const { return Vec4(this->x + vec.x, this->y + vec.y, this->z + vec.z, w + vec.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator-(const Vec4& vec) const { return Vec4(this->x - vec.x, this->y - vec.y, this->z - vec.z, w - vec.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator*(const Vec4& vec) const { return Vec4(this->x * vec.x, this->y * vec.y, this->z * vec.z, w * vec.w); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator/(const Vec4& vec) const { return Vec4(this->x / vec.x, this->y / vec.y, this->z / vec.z, w / vec.w); }

    template<typename T>
    Vec4<T> Vec4<T>::operator+(const T& value) const { return Vec4(this->x + value, this->y + value, this->z + value, this->w + value); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator-(const T& value) const { return Vec4( this->x - value, this->y - value, this->z - value, this->w - value); }

    template<typename T>
    Vec4<T> Vec4<T>::operator*(const T& value) const { return Vec4(this->x * value, this->y * value, this->z * value, this->w * value); }
    
    template<typename T>
    Vec4<T> Vec4<T>::operator/(const T& value) const { return Vec4( this->x / value, this->y / value, this->z / value, this->w / value); }

    /* Vector x= Vector */
    template<typename T>
    Vec4<T>& Vec4<T>::operator+=(const Vec4<T>& other) { this->x += other.x; this->y += other.y; this->z += other.z; this->w += other.w; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator-=(const Vec4<T>& other) { this->x -= other.x; this->y -= other.y; this->z -= other.z; this->w -= other.w; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator*=(const Vec4<T>& other) { this->x *= other.x; this->y *= other.y; this->z *= other.z; this->w *= other.w; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator/=(const Vec4<T>& other) { this->x /= other.x; this->y /= other.y; this->z /= other.z; this->w /= other.w; return *this; }

    /* Vector x= arbirary values */
    template<typename T>
    Vec4<T>& Vec4<T>::operator+=(const T& other) { this->x += other; this->y += other; this->z += other; this->w += other; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator-=(const T& other) { this->x -= other; this->y -= other; this->z -= other; this->w -= other; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator*=(const T& other) { this->x *= other; this->y *= other; this->z *= other; this->w *= other; return *this; }
    
    template<typename T>
    Vec4<T>& Vec4<T>::operator/=(const T& other) { this->x /= other; this->y /= other; this->z /= other; this->w /= other; return *this; }


    template<typename T>
    bool Vec4<T>::operator==(const Vec4<T>& other) const { return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w; }
    
    template<typename T>
    bool Vec4<T>::operator!=(const Vec4<T>& other) const { return !(*this == other); }

    template<typename T>
    Vec4<T>& Vec4<T>::clamp(const T& min_value, const T& max_value) {
        this->x = bebone::core::clamp(this->x, min_value, max_value);
        this->y = bebone::core::clamp(this->y, min_value, max_value);
        this->z = bebone::core::clamp(this->z, min_value, max_value);
        this->w = bebone::core::clamp(this->w, min_value, max_value);

        return *this;
    }
    
    template<typename T>
    Vec4<T>& Vec4<T>::clamp(const Vec4<T>& min_value, const Vec4<T>& max_value) {
        this->x = bebone::core::clamp(this->x, min_value.x, max_value.x);
        this->y = bebone::core::clamp(this->y, min_value.y, max_value.y);
        this->z = bebone::core::clamp(this->z, min_value.z, max_value.z);
        this->w = bebone::core::clamp(this->w, min_value.w, max_value.w);

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
        ss << this->x << ' ' << this->y << ' ' << this->z << ' ' << w; 
        return ss.str();
    }

    /**
     * @brief Converts all values of the vector to their absolute values
     * 
     * @return Vec2<T>& reference to vector instance
    */
    template<typename T>
    Vec4<T>& Vec4<T>::abs() {
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
    template<typename T>
    f32 Vec4<T>::length() const {
        return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z,  + this->w * this->w);
    }
}

#endif
