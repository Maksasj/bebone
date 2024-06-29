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
            shared_ptr<State> game_state;
            shared_ptr<GameObject> flappy_bird;
            shared_ptr<Input> input;

            std::function<void()> transition_function;
        public:
            MainMenuState(shared_ptr<GameObject> flappy_bird, const shared_ptr<Input>& input);
            ~MainMenuState() override;

            void enter() override;
            void update() override {};
            void exit() override;
            
            void set_game_state(shared_ptr<State> game_state);
    };
}

#endif
