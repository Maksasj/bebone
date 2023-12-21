#include "game_object.h"

namespace game::core::ecs {
    GameObject::GameObject(const string& name) : name(name) {
        transform = make_shared<Transform>();
    }
    
    GameObject::GameObject(const string& name, const Vec2f& position) : name(name) {
        transform = make_shared<Transform>(position);
    }

    shared_ptr<Transform>& GameObject::get_transform() {
        return transform;
    }

    string GameObject::get_name() const {
        return name;
    }

    void GameObject::update() {
        update_components();
    }
}
