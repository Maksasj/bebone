#ifndef _END_GAME_STATE_H_
#define _END_GAME_STATE_H_

#include <memory>

#include "state.h"
#include "../state_machine.h"

namespace game::core::fsm {
    using namespace std;
    
    class EndGameState : public State {
        private:
            shared_ptr<State> gameState;
        
        public:
            EndGameState();
            ~EndGameState();

            void enter();
            void update() {};
            void exit() {};

            void set_game_state(shared_ptr<State> gameState);
            void transition_to_game_state();
    };
}

#endif
