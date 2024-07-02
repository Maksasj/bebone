#include "collider.h"

namespace game::core::ecs {
    Collider::Collider(const Vec2f& local_top_left, const Vec2f& local_bottom_right, const bool& is_trigger) : top_left(local_top_left), bottom_right(local_bottom_right), trigger(is_trigger) { }

    Vec2f Collider::get_top_left() const {
        return top_left;
    }

    Vec2f Collider::get_bottom_right() const {
        return bottom_right;
    }

    bool Collider::is_trigger() const {
        return trigger;
    }

    void Collider::enter_trigger() {
        if (trigger) {
            triggered = true;
        }
    }

    void Collider::exit_trigger() {
        triggered = false;
    }

    bool Collider::is_triggered() const {
        if (trigger) {
            return triggered;
        }

        return false;
    }
}