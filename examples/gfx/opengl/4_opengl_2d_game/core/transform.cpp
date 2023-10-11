#include "transform.h"

namespace game::core {
    Transform::Transform() : position(Vec2f(0, 0)) { }
    Transform::Transform(const Vec2f& position) : position(position) { }

    Vec2f Transform::get_position() const {
        return position;
    }

    void Transform::set_position(const Vec2f& newPosition) {
        position = newPosition;
    }
}
