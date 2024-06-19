/**
 * @file
 * color_rgba32f.tpp
 *
 * @author
 * Maksim Jaroslavcevas radioboos@gmail.com
 *
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_COLOR_R32G32B32A32_FLOAT_TPP_
#define _OMNI_TYPES_COLOR_R32G32B32A32_FLOAT_TPP_

#include "color.tpp"
#include "color_format.h"

namespace omni::types {
    template<>
    struct Color<R32G32B32A32_FLOAT> {
        f32 r, g, b, a;
        
        static const Color<R32G32B32A32_FLOAT> BLACK;
        static const Color<R32G32B32A32_FLOAT> WHITE;
        static const Color<R32G32B32A32_FLOAT> RED;
        static const Color<R32G32B32A32_FLOAT> BLUE;
        static const Color<R32G32B32A32_FLOAT> GREEN;
        static const Color<R32G32B32A32_FLOAT> YELLOW;
        static const Color<R32G32B32A32_FLOAT> MAGENTA;
        static const Color<R32G32B32A32_FLOAT> CYAN;

        operator Vec4<f32>() const { return { r, g, b, a }; }

        template<class _DesiredColor>
        _DesiredColor to() const;

        static inline constexpr ColorFormat get_format() {
            return R32G32B32A32_FLOAT;
        }

        static inline constexpr size_t get_channels() {
            return 4;
        }

        static inline constexpr Color<R32G32B32A32_FLOAT> splat(const f32& v) {
            return {v, v, v, 1.0f};
        }

        static inline constexpr Color<R32G32B32A32_FLOAT> monochrome(const f32& v) {
            return splat(v);
        }

        #ifdef OMNI_GLAD_INTEGRATION
        static inline constexpr GLuint get_gl_format() {
            return GL_RGBA;
        }

        static inline constexpr GLuint get_gl_type() {
            return GL_FLOAT;
        }
        #endif

        static inline Color<R32G32B32A32_FLOAT> random() {
            return { 
                static_cast<f32>(static_cast<u8>(OMNI_TYPES_RAND % 255)) / 255.0f, 
                static_cast<f32>(static_cast<u8>(OMNI_TYPES_RAND % 255)) / 255.0f, 
                static_cast<f32>(static_cast<u8>(OMNI_TYPES_RAND % 255)) / 255.0f,
                1.0f
            };
        }
    };
}

#endif
