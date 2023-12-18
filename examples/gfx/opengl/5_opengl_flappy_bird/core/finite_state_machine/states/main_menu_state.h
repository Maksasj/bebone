#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include <memory>

#include "state.h"
#include "../state_machine.h"

namespace game::core::fsm {
    using namespace std;

    class MainMenuState : public State {
        private:
            shared_ptr<State> gameState;

        public:
            MainMenuState();
            ~MainMenuState();

            void enter();
            void update() {};
            void exit() {};
            
            void set_game_state(shared_ptr<State> gameState);
            void transition_to_game_state();
    };
}

#endif
