#ifndef _OBJECT_H_
#define _OBJECT_H_

//#include <vector>
#include <memory>
#include <map>
#include <typeindex>
#include "i_component.h"

namespace game::core::ecs {
    using namespace std;

    class Object : private bebone::core::NonCopyable {
        private:
            map<type_index, vector<shared_ptr<IComponent>>> components;

            type_index get_type(shared_ptr<IComponent> component);
            vector<shared_ptr<IComponent>>& get_component_vector(const type_index& type);

        public:
            Object();
            void add_component(shared_ptr<IComponent> component);
            void remove_component(shared_ptr<IComponent> component);
            void update_components();

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
