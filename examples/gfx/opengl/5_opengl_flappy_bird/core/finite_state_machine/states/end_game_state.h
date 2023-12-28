#ifndef _END_GAME_STATE_H_
#define _END_GAME_STATE_H_

#include <memory>

#include "state.h"
#include "../state_machine.h"

#include "../../entity_component_system/game_object.h"

namespace game::core::fsm {
    using namespace std;
    using namespace ecs; 
    
    class EndGameState : public State {
        private:
            shared_ptr<State> menuState;
            shared_ptr<GameObject> flappyBird;
        
        public:
            EndGameState(shared_ptr<GameObject> flappyBird);
            ~EndGameState();

            void enter();
            void update() {};
            void exit();

            void set_menu_state(shared_ptr<State> menuState);
            void transition_to_menu_state();
    };
}

#endif
