#ifndef _I_COMPONENT_H_
#define _I_COMPONENT_H_

#include "bebone/bebone.h"

namespace game::core::ecs {
    class IComponent : private bebone::core::NonCopyable {
    public:
        virtual void update() = 0;
        virtual ~IComponent() { }
    };
}

#endif
