#include "game_object.h"

namespace game::core::ecs {
    GameObject::GameObject(const string& name) : name(name) {
        transform = make_shared<Transform>();
        components = map<type_index, vector<shared_ptr<Component>>>();
    }
    
    GameObject::GameObject(const string& name, const Vec3f& position) : name(name) {
        transform = make_shared<Transform>(position);
        components = map<type_index, vector<shared_ptr<Component>>>();
    }

    shared_ptr<Transform>& GameObject::get_transform() {
        return transform;
    }

    string GameObject::get_name() const {
        return name;
    }

    void GameObject::update() {
        for (auto mapIt = components.begin(); mapIt != components.end(); ++mapIt) {
            auto v = (*mapIt).second;
            auto vIt = v.begin();
            
            while (vIt != v.end()) {
                (*vIt)->update();
                ++vIt;
            }
        }
    }

    void GameObject::remove_component(shared_ptr<Component> component) {
        type_index type = get_type(component);
        auto& v = get_component_vector(type);

        if (v.empty()) {
            return;
        }

        auto it = find(v.begin(), v.end(), component);
        if (it != v.end()) {
            v.erase(it);
        }
    }

    type_index GameObject::get_type(shared_ptr<Component> component) {
        auto ptr = component.get();
        return type_index(typeid(*ptr));
    }

    vector<shared_ptr<Component>>& GameObject::get_component_vector(const type_index& type) {
        return components[type];
    }

    void Component::set_transform(shared_ptr<Transform> transform) {
        this->transform = transform;
    }

    shared_ptr<Transform>& Component::get_transform() {
        return transform;
    }

    void Component::disable() {
        enabled = false;
    }

    void Component::enable() {
        enabled = true;
    }

    bool Component::is_enabled() {
        return enabled;
    }
}
