#include "game_object.h"

namespace game::core {
    GameObject::GameObject() : transform() {}
    GameObject::GameObject(const Transform& transform) : transform(transform) {}

    Transform& GameObject::get_transform() {
        return transform;
    }

    void GameObject::update() {
        update_components();
    }
}
