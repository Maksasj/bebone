#include "flying.h"

#include <cmath>

namespace game::core::ecs {
    Flying::Flying(const float& fly_force, const shared_ptr<Input>& input) : velocity_y(0.0f), fly_force(fly_force), input(input) {
        fly_function = std::function<void()>([this]() {
            set_velocity(this->fly_force);
        });
    }

    void Flying::update() {
        velocity_y += Time::delta_time * -gravity;
        auto& transform = get_transform();

        transform->set_position(Vec3f(transform->get_position().x, transform->get_position().y + velocity_y, transform->get_position().z));
        
        if (velocity_y < 0) {
            float rot_z = transform->get_rotation();
            rot_z += rot_z_alteration_speed * Time::delta_time * std::abs(velocity_y * 2);

            if (rot_z > min_rot_z) {
                transform->set_rotation(rot_z);
            }
        }
    }

    void Flying::set_velocity(const float& velocity) {
        velocity_y = velocity;
        get_transform()->set_rotation(this->max_rot_z);
    }

    void Flying::enable() {
        Component::enable();
        input->register_key_action(KeyCode::MouseButtonLeft, fly_function);
    }

    void Flying::disable() {
        Component::disable();
        input->remove_key_action(KeyCode::MouseButtonLeft, fly_function);
    }
}