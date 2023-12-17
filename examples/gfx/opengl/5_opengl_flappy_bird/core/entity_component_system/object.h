#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <vector>
#include <memory>
#include "i_component.h"

namespace game::core::ecs {
    class Object : private bebone::core::NonCopyable {
        private:
            std::vector<std::shared_ptr<IComponent>> components;
        
        public:
            void add_component(std::shared_ptr<IComponent> component);
            void get_component(std::shared_ptr<IComponent>& component);
            void remove_component(std::shared_ptr<IComponent> component);
            void update_components();
    };
}

#endif
