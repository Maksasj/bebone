#include "cyclic_movement.h"

#include "../../rng.h"

namespace game::core::ecs {
    CyclicMovement::CyclicMovement(const float& end_x_point, const float& start_x_point, const bool& randomize_y) :
            randomize_y(randomize_y), end_x_point(end_x_point), start_x_point(start_x_point) { }

    void CyclicMovement::update() {
        Vec3f movement = Vec3f::left * speed * Time::get_delta_time();
        auto& transform = get_transform();

        if (transform->get_position().x + movement.x < end_x_point) {
            float y = transform->get_position().y;

            if (randomize_y) {
                y = Random::rand(min_y, max_y);
            }

            transform->set_position(Vec3f(start_x_point, y, transform->get_position().z));
        } else {
            transform->move(movement);
        }
    }
}