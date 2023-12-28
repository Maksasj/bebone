#include "math_extension.h"

namespace game::core {
    double Math::deg_to_rad(const float& angle) {
        return angle * PI / 180;
    }
}