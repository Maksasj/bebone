#include "flying.h"

#include <cmath>

namespace game::core::ecs {
    Flying::Flying(const float& flyForce) : velocityY(0.0f), flyForce(flyForce) {
        flyFunction = std::function<void()>([this]() {
            set_velocity(this->flyForce);
        });
    }

    void Flying::update() {
        velocityY += Time::deltaTime * -gravity;
        auto& transform = get_transform();

        transform->set_position(Vec3f(transform->get_position().x, transform->get_position().y + velocityY, transform->get_position().z));
        
        if (velocityY < 0) {
            float rotZ = transform->get_rotation();
            rotZ += rotZAlterationSpeed * Time::deltaTime * std::abs(velocityY * 2);

            if (rotZ > minRotZ) {
                transform->set_rotation(rotZ);
            }
        }
    }

    void Flying::set_velocity(const float& velocity) {
        velocityY = velocity;
        get_transform()->set_rotation(this->maxRotZ);
    }

    void Flying::enable() {
        Component::enable();
        Input::get_instance().register_key_action(KeyCode::MouseButtonLeft, flyFunction);
    }

    void Flying::disable() {
        Component::disable();
        Input::get_instance().remove_key_action(KeyCode::MouseButtonLeft, flyFunction);
    }
}