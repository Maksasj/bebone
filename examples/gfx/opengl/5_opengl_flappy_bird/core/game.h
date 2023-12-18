#ifndef _GAME_H_
#define _GAME_H_

#include <memory>

#include "bebone/bebone.h"
#include "game_time.h"
#include "batch.h"
#include "sprite.h"

#include "finite_state_machine/state_machine.h"
#include "finite_state_machine/states/main_menu_state.h"
#include "finite_state_machine/states/game_state.h"
#include "finite_state_machine/states/end_game_state.h"

namespace game::core {
    using namespace std;
    using namespace fsm;

    class Game : private bebone::core::NonCopyable {
        private:
            shared_ptr<Batch> batch;
            shared_ptr<OrthographicCamera> camera;

            shared_ptr<GameObject> gameObject;

            shared_ptr<MainMenuState> mainMenuState;
            shared_ptr<GameState> gameState;
            shared_ptr<EndGameState> endGameState;
        public:
            Game(const unsigned int& width, const unsigned int& height);
            void update();
    };
}

#endif
