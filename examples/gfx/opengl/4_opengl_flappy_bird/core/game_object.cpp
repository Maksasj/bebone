#include "game_object.h"

namespace game::core {
    GameObject::GameObject(const Transform& transform) : transform(transform) {}

    const Transform& GameObject::get_transform() const {
        return transform;
    }

    void GameObject::update() {
        update_components();
    }
}
