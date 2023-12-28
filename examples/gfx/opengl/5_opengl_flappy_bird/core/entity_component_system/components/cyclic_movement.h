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
            Vec3f direction = Vec3f(-1.0f, 0.0f, 0.0f);
            float speed = 2.5f;

            bool randomizeY = false;
            float minY = -3.0f;
            float maxY = 4.5f;

            float endXPoint;
            float startXPoint;

        public:
            CyclicMovement(const float& endXPoint, const float& startXPoint, const bool& randomizeY = false);

            void update();
    };
}

#endif
