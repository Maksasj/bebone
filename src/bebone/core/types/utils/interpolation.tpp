#ifndef _BEBONE_CORE_TYPES_INTERPOLATION_TPP_
#define _BEBONE_CORE_TYPES_INTERPOLATION_TPP_

#include "../primitive_types.h"

namespace bebone::core {
    template<typename T>
    inline T clamp(const T& value, const T& min_value, const T& max_value) {
        if(value < min_value) return min_value;
        if(value > max_value) return max_value;
        
        return value;
    }

    template<typename T>
    inline T lerp(const T& start, const T& finish, const f32& t) {
        return (finish * t) + start * (1.0f - t);
    }

    template<typename T>
    inline T smoothstep(const T& start, const T& finish, const f32& t) {
        const f32 v1 = t * t;
        const f32 v2 = 1.0f - (1.0f - t) * (1.0f - t);
        const f32 new_t = lerp(v1, v2, t);

        return lerp(start, finish, new_t);
    }
}

#endif
