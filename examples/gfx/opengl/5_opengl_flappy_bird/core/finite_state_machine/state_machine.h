#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "state.h"

namespace game::core::finite_state_machine {
    class StateMachine {
    private:
        State* currentState;

    public:
        StateMachine() {}
        StateMachine(State& initialState);

        void set_state(State& state);
        void update_current_state();
    };
}

#endif
