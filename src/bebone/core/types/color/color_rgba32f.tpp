#ifndef _BEBONE_CORE_TYPES_COLOR_R32G32B32A32_FLOAT_TPP_
#define _BEBONE_CORE_TYPES_COLOR_R32G32B32A32_FLOAT_TPP_

#include "color.tpp"
#include "color_format.h"

namespace bebone::core {
    template<>
    struct Color<R32G32B32A32Float> {
        f32 r, g, b, a;
        
        static const Color<R32G32B32A32Float> BLACK;
        static const Color<R32G32B32A32Float> WHITE;
        static const Color<R32G32B32A32Float> RED;
        static const Color<R32G32B32A32Float> BLUE;
        static const Color<R32G32B32A32Float> GREEN;
        static const Color<R32G32B32A32Float> YELLOW;
        static const Color<R32G32B32A32Float> MAGENTA;
        static const Color<R32G32B32A32Float> CYAN;

        operator Vec4<f32>() const { return { r, g, b, a }; }

        template<class DesiredColor>
        DesiredColor to() const;

        static inline constexpr ColorFormat get_format() {
            return R32G32B32A32Float;
        }

        static inline constexpr size_t get_channels() {
            return 4;
        }

        static inline constexpr Color<R32G32B32A32Float> splat(const f32& v) {
            return {v, v, v, 1.0f};
        }

        static inline constexpr Color<R32G32B32A32Float> monochrome(const f32& v) {
            return splat(v);
        }

        static inline constexpr GLuint get_gl_format() {
            return GL_RGBA;
        }

        static inline constexpr VkFormat get_vulkan_format() {
            return VK_FORMAT_R32G32B32A32_SFLOAT;
        }

        static inline constexpr GLuint get_gl_type() {
            return GL_FLOAT;
        }

        static inline Color<R32G32B32A32Float> random() {
            return { 
                static_cast<f32>(static_cast<u8>(BEBONE_TYPES_RAND % 255)) / 255.0f, 
                static_cast<f32>(static_cast<u8>(BEBONE_TYPES_RAND % 255)) / 255.0f, 
                static_cast<f32>(static_cast<u8>(BEBONE_TYPES_RAND % 255)) / 255.0f,
                1.0f
            };
        }
    };
}

#endif
