#ifndef _CYCLIC_MOVEMENT_H_
#define _CYCLIC_MOVEMENT_H_

#include <memory>

#include "bebone/bebone.h"

#include "../game_object.h"
#include "../transform.h"

namespace game::core::ecs {
    using namespace bebone::core;
    using namespace std;

    class CyclicMovement : public Component {
        private:
            float speed = 2.5f;

            bool randomize_y = false;
            float min_y = -3.0f;
            float max_y = 4.5f;

            float end_x_point;
            float start_x_point;

        public:
            CyclicMovement(const float& end_x_point, const float& start_x_point, const bool& randomize_y = false);

            void update() override;
    };
}

#endif
