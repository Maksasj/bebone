#ifndef _FLYING_H_
#define _FLYING_H_

#include <memory>

#include "bebone/bebone.h"

#include "../component.h"
#include "../transform.h"

#include "../../game_time.h"

namespace game::core::ecs {
    using namespace bebone::core;
    using namespace std;

    class Flying : public Component {
        private:
            float velocityY;
            float flyForce;
            const float gravity = 0.1f;
            shared_ptr<Transform> transform;

        public:
            Flying(shared_ptr<Transform> transform, float flyForce);
            ~Flying();

            void update();

            float get_velocity() const;
            void set_velocity(const float& velocity);
    };
}

#endif
