#ifndef _STATE_H_
#define _STATE_H_

#include "bebone/bebone.h"

namespace game::core::finite_state_machine {
    class State {
        public:
            virtual void enter() = 0;
            virtual void update() = 0;
            virtual void exit() = 0;
    };
}

#endif
