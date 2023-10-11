#include "object.h"
#include <algorithm>

namespace game::core {
    void Object::add_component(std::shared_ptr<IComponent>& component) {
        components.push_back(component);
    }

    void Object::remove_component(std::shared_ptr<IComponent>& component) {
        auto it = std::find(components.begin(), components.end(), component);

        if (it != components.end()) {
            components.erase(it);
        }
    }

    void Object::update_components() {
        for (auto it = components.begin(); it != components.end(); ++it) {
            (*it)->update();
        }
    }
}
