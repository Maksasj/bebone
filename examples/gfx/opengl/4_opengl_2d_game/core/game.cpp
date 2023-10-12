#include "game.h"

namespace game::core {
    Game::Game() : mainMenuState(MainMenuState()), stateMachine(mainMenuState) { }

    void Game::update() {
        stateMachine.update_current_state();
    }
}