#include "cyclic_movement.h"

#include "../../game_time.h"

namespace game::core::ecs {
    CyclicMovement::CyclicMovement(const Vec3f& movementDirection, const Vec3f& endPoint, const Vec3f& startPoint) : 
        movementDirection(movementDirection), endPoint(endPoint), startPoint(startPoint) { }


    void CyclicMovement::update() {
        if (!is_enabled()) {
            return;
        }

        auto movement = movementDirection * Time::deltaTime;
        get_transform()->move(movement);
    }
}