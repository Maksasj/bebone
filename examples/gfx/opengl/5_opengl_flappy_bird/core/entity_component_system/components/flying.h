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
            float velocityY;
            const float gravity = 0.1f;
            float flyForce;

            float rotZAlterationSpeed = -550.0f;
            float minRotZ = -85.0f;
            float maxRotZ = 25.0f;

            std::shared_ptr<Input> input;

            std::function<void()> flyFunction;
            
        public:
            explicit Flying(const float& flyForce, const std::shared_ptr<Input>& input);

            void update() override;

            void set_velocity(const float& velocity);

            void enable() override;
            void disable() override;
    };
}

#endif
