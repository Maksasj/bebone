#ifndef _MATH_EXTENSION_H_
#define _MATH_EXTENSION_H_

#include "bebone/bebone.h"

namespace game::core {
    class Math : private bebone::core::NonCopyable {
        public:
            constexpr static double PI = 3.14159265358979323846;

            double static deg_to_rad(const float& angle);
    };
}

#endif
