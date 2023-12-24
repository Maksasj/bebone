#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include <memory>
#include <map>
#include <typeindex>
#include "component.h"

namespace game::core::ecs {
    using namespace std;

    class Object : private bebone::core::NonCopyable {
        private:
            map<type_index, vector<shared_ptr<Component>>> components;

            type_index get_type(shared_ptr<Component> component);
            vector<shared_ptr<Component>>& get_component_vector(const type_index& type);

        protected:
            void update_components();
        
        public:
            Object();

            void remove_component(shared_ptr<Component> component);

            template <typename T, typename... Args>
            shared_ptr<T> add_component(Args&&... args) {
                static_assert(std::is_base_of<Component, T>::value, "T must be a Component");

                auto component = std::make_shared<T>(std::forward<Args>(args)...);
                type_index type = get_type(component);
                components[type].push_back(component);

                return component;
            }

            template <typename T>
            shared_ptr<T> get_component() {
                auto v = components[typeid(T)];
                
                if (!v.empty()) {
                    return dynamic_pointer_cast<T>(v[0]);
                }
                
                return nullptr;
            }
    };
}

#endif
