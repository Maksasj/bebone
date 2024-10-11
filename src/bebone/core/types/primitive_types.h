#ifndef _BEBONE_CORE_TYPES_PRIMITIVE_TYPES_H_
#define _BEBONE_CORE_TYPES_PRIMITIVE_TYPES_H_

#include <cstdint>
#include <stdlib.h>

namespace bebone::core {
    using u8 =  uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    using i8 =  int8_t;
    using i16 = int16_t;
    using i32 = int32_t;
    using i64 = int64_t;

    using f32 = float;
    using f64 = double;
}

#define BEBONE_PI (f32) 3.14159265359f

#endif
