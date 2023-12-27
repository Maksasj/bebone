#include "collider.h"

namespace game::core::ecs {
    Collider::Collider(const Vec2f& localTopLeft, const Vec2f& localBottomRight, const bool& isTrigger) : topLeft(localTopLeft), bottomRight(localBottomRight), isTrigger(isTrigger) { }

    Vec2f Collider::get_top_left() const {
        return topLeft;
    }

    Vec2f Collider::get_bottom_right() const {
        return bottomRight;
    }

    bool Collider::is_trigger() const {
        return isTrigger;
    }

    void Collider::enter_trigger() {
        if (isTrigger) {
            triggered = true;
        }
    }

    void Collider::exit_trigger() {
        triggered = false;
    }

    bool Collider::is_triggered() const {
        if (isTrigger) {
            return triggered;
        }

        return false;
    }
}