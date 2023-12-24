#ifndef _CYCLIC_MOVEMENT_H_
#define _CYCLIC_MOVEMENT_H_

#include <memory>

#include "bebone/bebone.h"

#include "../component.h"
#include "../transform.h"

namespace game::core::ecs {
    using namespace bebone::core;
    using namespace std;

    class CyclicMovement : public Component {
        private:
            shared_ptr<Transform> transform;
            Vec3f movementDirection;
            float movementSpeed = 5.0f;

            Vec3f endPoint;
            Vec3f startPoint;

        public:
            CyclicMovement(shared_ptr<Transform> transform, const Vec3f& movementDirection, const Vec3f& endPoint, const Vec3f& startPoint);
            ~CyclicMovement();

            void update();
    };
}

#endif
