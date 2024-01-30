#ifndef _BEBONE_CORE_TYPES_H_
#define _BEBONE_CORE_TYPES_H_

#include <omni_types.tpp>

namespace bebone::core {
    using u8  = omni::types::u8;
    using u16 = omni::types::u16;
    using u32 = omni::types::u32;
    using u64 = omni::types::u64;

    using i8 =  omni::types::i8;
    using i16 = omni::types::i16;
    using i32 = omni::types::i32;
    using i64 = omni::types::i64;

    using f32 = omni::types::f32;
    using f64 = omni::types::f64;

    using Vec2f = omni::types::Vec2f;
    using Vec3f = omni::types::Vec3f;
    using Vec4f = omni::types::Vec4f;

    using Vec2i = omni::types::Vec2i;
    using Vec3i = omni::types::Vec3i;
    using Vec4i = omni::types::Vec4i;

    using Mat4f = omni::types::Mat4f;
    using Mat2f = omni::types::Mat2f;

    using ColorFormat = omni::types::ColorFormat;

    template<ColorFormat _Format>
    using Color = omni::types::Color<_Format>;

    using ColorRGB24 = omni::types::ColorRGB24;
    using ColorRGBA32 = omni::types::ColorRGBA32;
    using ColorRGBA32f = omni::types::ColorRGBA32f;

    // Default color types is R32G32B32A32_FLOAT
    using ColorRGBA = ColorRGBA32f;
}

#endif
