#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "bebone/bebone.h"

namespace game::core::ecs {
    class Component : private bebone::core::NonCopyable {
    public:
        virtual void update() = 0;
        virtual ~Component() { }
    };
}

#endif
