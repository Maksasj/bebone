#include "transform.h"

namespace game::core {
    Transform::Transform() : scale(1.0f) {}

    Transform::Transform(const Vec3f& position, const Vec3f& rotation, const f32& scale) : 
        position(position), rotation(rotation), scale(scale) { }

    const Vec3f& Transform::get_position() const {
        return position;
    }

    void Transform::set_position(const Vec3f& newPosition) {
        position = newPosition;
    }

    const Vec3f& Transform::get_rotation() const {
        return rotation;
    }

    void Transform::set_rotation(const Vec3f& newRotation) {
        rotation = newRotation;
    }

    const f32& Transform::get_scale() const {
        return scale;
    }

    void Transform::set_scale(const f32& newScale) {
        scale = newScale;
    }
}
