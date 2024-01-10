#include "transform.h"

namespace game::core::ecs {
    Transform::Transform() : 
        position(Vec3f::zero), rotation(0.0f), scale(1.0f) { }

    Transform::Transform(const Vec3f& position) : 
        position(position), rotation(0.0f), scale(1.0f) { }

    Transform::Transform(const Vec3f& position, const f32& rotation, const f32& scale) : 
        position(position), rotation(rotation), scale(scale) { }

    const Vec3f& Transform::get_position() const {
        return position;
    }

    void Transform::set_position(const Vec3f& newPosition) {
        position = newPosition;
    }

    const f32& Transform::get_rotation() const {
        return rotation;
    }

    void Transform::set_rotation(const f32& newRotation) {
        rotation = newRotation;
    }

    const f32& Transform::get_scale() const {
        return scale;
    }

    void Transform::set_scale(const f32& newScale) {
        scale = newScale;
    }

    void Transform::move(const Vec3f& v) {
        position += v;
    }
}