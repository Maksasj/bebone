#ifndef _MAIN_MENU_STATE_H_
#define _MAIN_MENU_STATE_H_

#include <memory>

#include "bebone/bebone.h"

#include "state.h"
#include "../state_machine.h"

#include "../../entity_component_system/game_object.h"

namespace game::core::fsm {
    using namespace std;
    using namespace ecs;

    class MainMenuState : public State {
        private:
            shared_ptr<State> gameState;
            shared_ptr<GameObject> flappyBird;

            shared_ptr<VoidFunction> transitionFunction;
        public:
            MainMenuState(shared_ptr<GameObject> flappyBird);
            ~MainMenuState() override;

            void enter() override;
            void update() override {};
            void exit() override;
            
            void set_game_state(shared_ptr<State> gameState);
    };
}

#endif
