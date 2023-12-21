#include "gravity.h"

#include "../../input_system/input.h"

namespace game::core::ecs {
    Gravity::Gravity(shared_ptr<Transform> transform) : velocityY(0.0f), transform(transform) {
        using namespace game::core::input_system;

        auto function = [this]() {
            set_velocity(0.06f);
        };
        Input::register_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON, Action(function));
    }

    Gravity::~Gravity() {
        transform = nullptr;
    }

    void Gravity::update() {
        velocityY += Time::deltaTime * -gravity;
        transform->set_position(Vec2f(transform->get_position().x, transform->get_position().y + velocityY));
    }

    float Gravity::get_velocity() const {
        return velocityY;
    }

    void Gravity::set_velocity(const float& velocity) {
        velocityY = velocity;
    }
}