#ifndef _BEBONE_CORE_TYPES_COLOR_FORMAT_H_
#define _BEBONE_CORE_TYPES_COLOR_FORMAT_H_

#define BEBONE_TYPES_COLOR_UINT 1
#define BEBONE_TYPES_COLOR_FLOAT 2

#define BEBONE_TYPES_COLOR_3_CHANNELS 4
#define BEBONE_TYPES_COLOR_4_CHANNELS 8

namespace bebone::core {
    enum ColorFormat {
        R8G8B8_UINT         = BEBONE_TYPES_COLOR_3_CHANNELS | BEBONE_TYPES_COLOR_UINT,
        R8G8B8A8_UINT       = BEBONE_TYPES_COLOR_4_CHANNELS | BEBONE_TYPES_COLOR_UINT,

        R32G32B32A32_FLOAT  = BEBONE_TYPES_COLOR_4_CHANNELS | BEBONE_TYPES_COLOR_FLOAT,

        RGB24 = R8G8B8_UINT,
        RGBA32 = R8G8B8A8_UINT,
        RGBA32f = R32G32B32A32_FLOAT
    };
}

#endif