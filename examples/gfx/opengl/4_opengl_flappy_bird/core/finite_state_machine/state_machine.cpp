#include "state_machine.h"

namespace game::core::finite_state_machine {
    StateMachine::StateMachine(State& initialState) {
        initialState.enter();
        currentState = &initialState;
    }

    void StateMachine::set_state(State& state) {
        if (currentState != nullptr) {
            currentState->exit();
        }
        
        state.enter();

        currentState = &state;
    }

    void StateMachine::update_current_state() {
        currentState->update();
    }
}
