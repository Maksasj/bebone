#ifndef _BEBONE_CORE_TYPES_COLOR_R8G8B8_UINT_TPP_
#define _BEBONE_CORE_TYPES_COLOR_R8G8B8_UINT_TPP_

#include "color.tpp"
#include "color_format.h"

namespace bebone::core {
    template<>
    struct Color<R8G8B8Uint> {
        u8 r, g, b;

        static const Color<R8G8B8Uint> BLACK;
        static const Color<R8G8B8Uint> WHITE;
        static const Color<R8G8B8Uint> RED;
        static const Color<R8G8B8Uint> BLUE;
        static const Color<R8G8B8Uint> GREEN;
        static const Color<R8G8B8Uint> YELLOW;
        static const Color<R8G8B8Uint> MAGENTA;
        static const Color<R8G8B8Uint> CYAN;

        operator Vec3<u8>() const { return { r, g, b }; }

        template<class DesiredColor>
        DesiredColor to() const;

        static inline constexpr ColorFormat get_format() {
            return R8G8B8Uint;
        }

        static inline constexpr size_t get_channels() {
            return 3;
        }

        static inline constexpr Color<R8G8B8Uint> splat(const u8& v) {
            return {v, v, v};
        }

        static inline constexpr Color<R8G8B8Uint> monochrome(const u8& v) {
            return splat(v);
        }

        static inline constexpr u32 get_gl_format() {
            return GL_RGB;
        }

        static inline constexpr u32 get_gl_type() {
            return GL_UNSIGNED_BYTE;
        }

        static inline Color<R8G8B8Uint> random() {
            return { 
                static_cast<u8>(BEBONE_TYPES_RAND % 255), 
                static_cast<u8>(BEBONE_TYPES_RAND % 255), 
                static_cast<u8>(BEBONE_TYPES_RAND % 255) 
            };
        }
    };
}

#endif
