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
            Vec3f movementDirection;
            float movementSpeed = 5.0f;

            Vec3f endPoint;
            Vec3f startPoint;

        public:
            CyclicMovement(const Vec3f& movementDirection, const Vec3f& endPoint, const Vec3f& startPoint);

            void update();
    };
}

#endif
