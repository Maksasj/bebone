#ifndef _GAME_H_
#define _GAME_H_

#include "bebone/bebone.h"
#include "finite_state_machine/state_machine.h"
#include "finite_state_machine/main_menu_state.h"

using namespace game::core::finite_state_machine;

namespace game::core {
    class Game : private bebone::core::NonCopyable {
        private:
            StateMachine stateMachine;
            MainMenuState mainMenuState;

        public:
            Game();
            void update();
    };
}

#endif
