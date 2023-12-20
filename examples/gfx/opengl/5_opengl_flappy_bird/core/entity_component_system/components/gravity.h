#ifndef _GRAVITY_H_
#define _GRAVITY_H_

#include "bebone/bebone.h"

#include "../component.h"
#include "../../game_time.h"

namespace game::core::ecs {
    using namespace bebone::core;

    class Gravity : public Component {
        private:
            float velocityY;
            const float gravity = 0.1f;

        public:
            void add_force(const float& forceY);
            void update();

            float get_velocity() const;
            void set_velocity(const float& velocity);
    };
}

#endif
