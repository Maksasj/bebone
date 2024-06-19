/**
 * @file
 * color_format.h
 *
 * @author
 * Maksim Jaroslavcevas radioboos@gmail.com
 *
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_COLOR_FORMAT_H_
#define _OMNI_TYPES_COLOR_FORMAT_H_

#define OMNI_TYPES_COLOR_UINT 1
#define OMNI_TYPES_COLOR_FLOAT 2

#define OMNI_TYPES_COLOR_3_CHANNELS 4
#define OMNI_TYPES_COLOR_4_CHANNELS 8

namespace bebone::core {
    enum ColorFormat {
        R8G8B8_UINT         = OMNI_TYPES_COLOR_3_CHANNELS | OMNI_TYPES_COLOR_UINT,
        R8G8B8A8_UINT       = OMNI_TYPES_COLOR_4_CHANNELS | OMNI_TYPES_COLOR_UINT,

        R32G32B32A32_FLOAT  = OMNI_TYPES_COLOR_4_CHANNELS | OMNI_TYPES_COLOR_FLOAT,

        RGB24 = R8G8B8_UINT,
        RGBA32 = R8G8B8A8_UINT,
        RGBA32f = R32G32B32A32_FLOAT
    };
}

#endif
