#include "action.h"

namespace game::core::input_system {
    Action::Action(std::function<void()> func) : func(func) { }
    Action::Action() : func(NULL) { }

    void Action::execute() {
        func();
    }

    void Action::set_function(std::function<void()> func) {
        this->func = func;
    }
}