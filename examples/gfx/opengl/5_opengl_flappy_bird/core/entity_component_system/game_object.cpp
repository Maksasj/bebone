#include "game_object.h"

namespace game::core {
    GameObject::GameObject(const std::string& name) : name(name), transform() {}
    GameObject::GameObject(const std::string& name, const Transform& transform) : name(name), transform(transform) {}

    Transform& GameObject::get_transform() {
        return transform;
    }

    std::string GameObject::get_name() const {
        return name;
    }

    void GameObject::update() {
        update_components();
    }
}
