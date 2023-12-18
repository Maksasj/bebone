#include "object.h"
#include <algorithm>

namespace game::core::ecs {
    Object::Object() {
        components = map<type_index, vector<shared_ptr<IComponent>>>();
    }

    void Object::add_component(shared_ptr<IComponent> component) {
        type_index type = get_type(component);
        components[type].push_back(component);
    }

    void Object::remove_component(shared_ptr<IComponent> component) {
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

    void Object::update_components() {
        for (auto mapIt = components.begin(); mapIt != components.end(); ++mapIt) {
            auto v = (*mapIt).second;
            auto vIt = v.begin();
            
            while (vIt != v.end()) {
                (*vIt)->update();
                ++vIt;
            }
        }
    }

    type_index Object::get_type(shared_ptr<IComponent> component) {
        auto ptr = component.get();
        return type_index(typeid(*ptr));
    }

    vector<shared_ptr<IComponent>>& Object::get_component_vector(const type_index& type) {
        return components[type];
    }
}
