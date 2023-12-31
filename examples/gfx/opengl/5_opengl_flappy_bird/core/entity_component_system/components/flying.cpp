#include "flying.h"

#include <cmath>
#include "../../input_system/input.h"

namespace game::core::ecs {
    Flying::Flying(const float& flyForce) : velocityY(0.0f), flyForce(flyForce) { }

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

    float Flying::get_velocity() const {
        return velocityY;
    }

    void Flying::set_velocity(const float& velocity) {
        velocityY = velocity;
        get_transform()->set_rotation(this->maxRotZ);
    }

    void Flying::enable() {
        using namespace game::core::input_system;

        Component::enable();

        auto flyFunction = [this]() {
            set_velocity(this->flyForce);
        };
        Input::register_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON, Action(flyFunction));
    }

    void Flying::disable() {
        using namespace game::core::input_system;

        Component::disable();

        Input::remove_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON);
    }
}