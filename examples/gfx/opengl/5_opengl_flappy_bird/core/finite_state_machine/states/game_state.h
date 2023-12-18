#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <memory>

#include "state.h"
#include "../state_machine.h"

namespace game::core::fsm {
    using namespace std;

    class GameState : public State {
        private:
            shared_ptr<State> endGameState;

        public:
            GameState();
            ~GameState();

            void enter();
            void update() {};
            void exit() {};

            void set_end_game_state(shared_ptr<State> endGameState);
            void transition_to_end_game_state();
    };
}

#endif
