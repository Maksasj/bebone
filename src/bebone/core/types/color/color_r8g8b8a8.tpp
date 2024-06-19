/**
 * @file
 * color_r8g8b8a8.tpp
 *
 * @author
 * Maksim Jaroslavcevas radioboos@gmail.com
 *
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_COLOR_R8G8B8A8_UINT_TPP_
#define _OMNI_TYPES_COLOR_R8G8B8A8_UINT_TPP_

#include "color.tpp"
#include "color_format.h"

namespace bebone::core {
    template<>
    struct Color<R8G8B8A8_UINT> {
        u8 r, g, b, a;

        static const Color<R8G8B8A8_UINT> BLACK;
        static const Color<R8G8B8A8_UINT> WHITE;
        static const Color<R8G8B8A8_UINT> RED;
        static const Color<R8G8B8A8_UINT> BLUE;
        static const Color<R8G8B8A8_UINT> GREEN;
        static const Color<R8G8B8A8_UINT> YELLOW;
        static const Color<R8G8B8A8_UINT> MAGENTA;
        static const Color<R8G8B8A8_UINT> CYAN;

        operator Vec4<u8>() const { return { r, g, b, a }; }

        template<class _DesiredColor>
        _DesiredColor to() const;

        static inline constexpr ColorFormat get_format() {
            return R8G8B8A8_UINT;
        }

        static inline constexpr size_t get_channels() {
            return 4;
        }

        static inline constexpr Color<R8G8B8A8_UINT> splat(const u8& v) {
            return {v, v, v, 255};
        }

        static inline constexpr Color<R8G8B8A8_UINT> monochrome(const u8& v) {
            return splat(v);
        }

        #ifdef OMNI_GLAD_INTEGRATION
        static inline constexpr GLuint get_gl_format() {
            return GL_RGBA;
        }

        static inline constexpr GLuint get_gl_type() {
            return GL_UNSIGNED_BYTE;
        }
        #endif

        static inline Color<R8G8B8A8_UINT> random() {
            return { 
                static_cast<u8>(OMNI_TYPES_RAND % 255), 
                static_cast<u8>(OMNI_TYPES_RAND % 255), 
                static_cast<u8>(OMNI_TYPES_RAND % 255),
                255 
            };
        }
    };
}

#endif
