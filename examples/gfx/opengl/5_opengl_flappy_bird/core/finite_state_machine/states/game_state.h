#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <memory>

#include "state.h"
#include "../state_machine.h"

#include "../../entity_component_system/game_object.h"

namespace game::core::fsm {
    using namespace std;
    using namespace ecs;

    class GameState : public State {
        private:
            shared_ptr<State> endGameState;
            shared_ptr<GameObject> flappyBird;
            
            shared_ptr<GameObject> ground1;
            shared_ptr<GameObject> ground2;
            shared_ptr<GameObject> ground3;

        public:
            GameState(shared_ptr<GameObject> flappyBird);
            ~GameState();

            void enter();
            void update();
            void exit();

            void set_end_game_state(shared_ptr<State> endGameState);
            void transition_to_end_game_state();
    };
}

#endif
