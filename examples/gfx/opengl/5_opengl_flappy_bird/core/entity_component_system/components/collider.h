#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "bebone/bebone.h"

#include "../game_object.h"

namespace game::core::ecs {
    using namespace bebone::core;

    class Collider : public Component {
        private:
            Vec2f topLeft;
            Vec2f bottomRight;

            bool isTrigger;
            bool triggered = false;

        public:
            Collider(const Vec2f& localTopLeft, const Vec2f& localBottomRight, const bool& isTrigger = false);
            void update() { }

            Vec2f get_top_left() const;
            Vec2f get_bottom_right() const;
            
            bool is_trigger() const;

            void enter_trigger();
            void exit_trigger();
            bool is_triggered() const;
    };
}

#endif
