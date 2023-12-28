#ifndef _STATE_H_
#define _STATE_H_

namespace game::core::fsm {
    class State {
        public:
            virtual ~State() { };
            virtual void enter() = 0;
            virtual void update() = 0;
            virtual void exit() = 0;
    };
}

#endif
