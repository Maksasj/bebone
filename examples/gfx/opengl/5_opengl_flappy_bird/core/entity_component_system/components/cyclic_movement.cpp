#include "cyclic_movement.h"

#include "../../game_time.h"

namespace game::core::ecs {
    CyclicMovement::CyclicMovement(shared_ptr<Transform> transform, const Vec3f& movementDirection, const Vec3f& endPoint, const Vec3f& startPoint) : 
        transform(transform), movementDirection(movementDirection), endPoint(endPoint), startPoint(startPoint) { }
    
    CyclicMovement::~CyclicMovement() {
        transform = nullptr;
    }

    void CyclicMovement::update() {
        auto movement = movementDirection * Time::deltaTime;
        transform->move(movement);
    }
}