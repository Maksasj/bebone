#include "gravity.h"

namespace game::core::ecs {
    void Gravity::add_force(const float& forceY) {
        velocityY += forceY;
    }

    void Gravity::update() {
        velocityY += Time::deltaTime * -gravity;
    }

    float Gravity::get_velocity() const {
        return velocityY;
    }

    void Gravity::set_velocity(const float& velocity) {
        velocityY = velocity;
    }
}