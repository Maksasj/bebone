#include "cyclic_movement.h"

#include "../../game_time.h"
#include "../../rng.h"

namespace game::core::ecs {
    CyclicMovement::CyclicMovement(const float& endXPoint, const float& startXPoint, const bool& randomizeY) : 
        randomizeY(randomizeY), endXPoint(endXPoint), startXPoint(startXPoint) { }

    void CyclicMovement::update() {
        Vec3f movement = direction * speed * Time::deltaTime;
        auto& transform = get_transform();

        if (transform->get_position().x + movement.x < endXPoint) {
            float y = transform->get_position().y;

            if (randomizeY) {
                y = Random::rand(minY, maxY);
            }

            transform->set_position(Vec3f(startXPoint, y, transform->get_position().z));
        } else {
            transform->move(movement);
        }
    }
}