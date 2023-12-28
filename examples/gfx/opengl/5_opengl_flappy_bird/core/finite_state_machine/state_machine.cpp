#include "state_machine.h"

namespace game::core::fsm {
    std::shared_ptr<State> StateMachine::currentState = nullptr;

    void StateMachine::set_state(std::shared_ptr<State> state) {
        if (currentState != nullptr) {
            currentState->exit();
        }
        
        state->enter();

        currentState = state;
    }

    void StateMachine::update_current_state() {
        currentState->update();
    }
}
