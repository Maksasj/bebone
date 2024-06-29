#include "state_machine.h"

namespace game::core::fsm {
    std::shared_ptr<State> StateMachine::current_state = nullptr;

    void StateMachine::set_state(std::shared_ptr<State> state) {
        if (current_state != nullptr) {
            current_state->exit();
        }
        
        state->enter();

        current_state = state;
    }

    void StateMachine::update_current_state() {
        current_state->update();
    }
}
