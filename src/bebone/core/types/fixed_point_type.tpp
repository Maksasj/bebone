#ifndef _BEBONE_CORE_TYPES_FIXED_POINT_TYPE_TPP_
#define _BEBONE_CORE_TYPES_FIXED_POINT_TYPE_TPP_

#include "primitive_types.h"

// Todo
namespace bebone::core {
    template<typename B, u64 point>
    class FixedPoint {
        private:
            B value;

            FixedPoint(const B new_value)
                    : value(new_value) {

            }

        public:
            FixedPoint()
                : value(0) {

            }

            FixedPoint operator+(const FixedPoint& another) const {
                return FixedPoint(value + another.value);
            }

            FixedPoint operator-(const FixedPoint& another) const {
                return FixedPoint(value - another.value);
            }

            FixedPoint operator*(const FixedPoint& another) const {
                return FixedPoint(value * another.value);
            }

            FixedPoint operator/(const FixedPoint& another) const {
                return FixedPoint(value / another.value);
            }
    };
}

#endif
