#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include <memory>
#include <map>
#include <typeindex>
#include "i_component.h"

namespace game::core::ecs {
    using namespace std;

    class Object : private bebone::core::NonCopyable {
        private:
            //vector<shared_ptr<IComponent>> components;
            multimap<type_index, shared_ptr<IComponent>> components;
        
        public:
            Object();
            void add_component(shared_ptr<IComponent> component);
            void remove_component(shared_ptr<IComponent> component);
            void update_components();

            template <typename T>
            shared_ptr<T> get_component() {
                return dynamic_pointer_cast<T>(components[typeid(T)]);
            }
    };
}

#endif
