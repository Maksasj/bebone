#ifndef _FLYING_H_
#define _FLYING_H_

#include <memory>

#include "bebone/bebone.h"

#include "../game_object.h"
#include "../transform.h"

#include "../../game_time.h"

namespace game::core::ecs {
    using namespace bebone::core;
    using namespace std;

    class Flying : public Component {
        private:
            float velocity_y;
            const float gravity = 0.1f;
            float fly_force;

            float rot_z_alteration_speed = -550.0f;
            float min_rot_z = -85.0f;
            float max_rot_z = 25.0f;

            std::function<void()> fly_function;
            
        public:
            explicit Flying(const float& fly_force);

            void update() override;

            void set_velocity(const float& velocity);

            void enable() override;
            void disable() override;
    };
}

#endif
