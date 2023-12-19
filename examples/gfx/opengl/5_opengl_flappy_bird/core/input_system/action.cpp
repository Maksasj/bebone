#include "action.h"

namespace game::core::input_system {
    Action::Action(std::function<void()> func) {
        this->func = func;
    }

    void Action::execute() {
        func();
    }
}