#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "bebone/bebone.h"
using namespace bebone::core;

namespace game::core {
    class Transform {
    private:
        Vec2f position;
    
    public:
        Transform();
        Transform(const Vec2f& position);

        Vec2f get_position() const;
        void set_position(const Vec2f& newPosition);
    };
}

#endif
