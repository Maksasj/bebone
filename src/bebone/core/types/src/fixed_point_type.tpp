/**
 * @file
 * fixed_point.tpp
 *
 * @author
 * Maksim Jaroslavcevas radioboos@gmail.com
 *
 * @copyright
 * see LICENSE.md file
*/

#ifndef _OMNI_TYPES_FIXED_POINT_TYPE_TPP_
#define _OMNI_TYPES_FIXED_POINT_TYPE_TPP_

#include "primitive_types.h"

// Todo
namespace omni::types {
    template<typename _B, u64 point>
    class FixedPoint {
        private:
            _B value;

            FixedPoint(const _B newValue)
                    : value(newValue) {

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
