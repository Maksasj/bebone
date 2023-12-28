#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "bebone/bebone.h"

#include <memory>
#include "states/state.h"

namespace game::core::fsm {
    class StateMachine : private bebone::core::NonCopyable {
    private:
        static std::shared_ptr<State> currentState;

    public:
        void static set_state(std::shared_ptr<State> state);
        void static update_current_state();
    };
}

#endif
