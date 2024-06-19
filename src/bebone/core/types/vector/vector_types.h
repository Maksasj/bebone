/**
 * @file 
 * vector_types.h
 * 
 * @author 
 * Maksim Jaroslavcevas radioboos@gmail.com
 * 
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_VECTOR_TYPES_H_
#define _OMNI_TYPES_VECTOR_TYPES_H_

#include <functional>

#include "../primitive_types.h"

#include "vector2_type.tpp"
#include "vector3_type.tpp"
#include "vector4_type.tpp"

namespace bebone::core {
    using Vec2f = Vec2<f32>;
    using Vec3f = Vec3<f32>;
    using Vec4f = Vec4<f32>;

    using Vec2i = Vec2<i32>;
    using Vec3i = Vec3<i32>;
    using Vec4i = Vec4<i32>;
}

namespace std {
    template<>
    struct hash<bebone::core::Vec2f> {
        size_t operator()(const bebone::core::Vec2f& key) const {
            return std::hash<bebone::core::f32>()(key.x) ^ std::hash<bebone::core::f32>()(key.y);
        }
    };

    template<>
    struct hash<bebone::core::Vec3f> {
        size_t operator()(const bebone::core::Vec3f& key) const {
            return
                std::hash<bebone::core::f32>()(key.x) ^
                std::hash<bebone::core::f32>()(key.y) ^
                std::hash<bebone::core::f32>()(key.z);
        }
    };

    template<>
    struct hash<bebone::core::Vec4f> {
        size_t operator()(const bebone::core::Vec4f& key) const {
            return
                std::hash<bebone::core::f32>()(key.x) ^
                std::hash<bebone::core::f32>()(key.y) ^
                std::hash<bebone::core::f32>()(key.z) ^
                std::hash<bebone::core::f32>()(key.w);
        }
    };

    template<>
    struct hash<bebone::core::Vec2i> {
        size_t operator()(const bebone::core::Vec2i& key) const {
            return std::hash<bebone::core::i32>()(key.x) ^ std::hash<bebone::core::i32>()(key.y);
        }
    };

    template<>
    struct hash<bebone::core::Vec3i> {
        size_t operator()(const bebone::core::Vec3i& key) const {
            return
                std::hash<bebone::core::i32>()(key.x) ^
                std::hash<bebone::core::i32>()(key.y) ^
                std::hash<bebone::core::i32>()(key.z);
        }
    };

    template<>
    struct hash<bebone::core::Vec4i> {
        size_t operator()(const bebone::core::Vec4i& key) const {
            return
                std::hash<bebone::core::i32>()(key.x) ^
                std::hash<bebone::core::i32>()(key.y) ^
                std::hash<bebone::core::i32>()(key.z) ^
                std::hash<bebone::core::i32>()(key.w);
        }
    };
}

#endif
