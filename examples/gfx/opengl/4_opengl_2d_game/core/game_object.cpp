#include "game_object.h"

namespace game::core {
    GameObject::GameObject() : transform(Transform()) {}
    GameObject::GameObject(const Vec2f& position) : transform(Transform(position)) {}

    const Transform& GameObject::get_transform() const {
        return transform;
    }

    void GameObject::update() {
        update_components();
    }
}
