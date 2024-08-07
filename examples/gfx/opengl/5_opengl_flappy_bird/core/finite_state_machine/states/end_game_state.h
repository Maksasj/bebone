#ifndef _END_GAME_STATE_H_
#define _END_GAME_STATE_H_

#include <memory>

#include "bebone/bebone.h"

#include "state.h"
#include "../state_machine.h"

#include "../../entity_component_system/game_object.h"

namespace game::core::fsm {
    using namespace std;
    using namespace ecs; 
    
    class EndGameState : public State {
        private:
            shared_ptr<State> menu_state;
            shared_ptr<GameObject> flappy_bird;
            shared_ptr<Input> input;

            std::function<void()> transition_function;
        public:
            EndGameState(shared_ptr<GameObject> flappy_bird, const shared_ptr<Input>& input);
            ~EndGameState() override;

            void enter() override;
            void update() override {};
            void exit() override;

            void set_menu_state(shared_ptr<State> menu_state);
    };
}

#endif
