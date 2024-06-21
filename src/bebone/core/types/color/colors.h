#ifndef _BEBONE_CORE_TYPES_COLORS_H_
#define _BEBONE_CORE_TYPES_COLORS_H_

#include "color.tpp"
#include "color_format.h"

#include "color_r8g8b8.tpp"
#include "color_r8g8b8a8.tpp"
#include "color_rgba32f.tpp"

namespace bebone::core {
    using ColorRGB24 = Color<RGB24>;
    using ColorRGBA32 = Color<RGBA32>;
    using ColorRGBA32f = Color<RGBA32f>;

    using ColorRGBA = ColorRGBA32f;
}

#endif
