#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include "state.h"

namespace game::core::finite_state_machine {
    class MainMenuState : public State {
        public:
            void enter() {};
            void update() {};
            void exit() {};
    };
}

#endif
