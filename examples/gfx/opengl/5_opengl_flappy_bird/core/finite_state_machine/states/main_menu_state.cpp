#include "main_menu_state.h"
#include <iostream>

namespace game::core::fsm {
    MainMenuState::MainMenuState() : gameState(nullptr) { }
    
    MainMenuState::~MainMenuState() {
        gameState = nullptr;
    }

    void MainMenuState::enter() {
        cout << "main menu state" << endl;
        transition_to_game_state();
    }

    void MainMenuState::set_game_state(shared_ptr<State> gameState) {
        this->gameState = gameState;
    }

    void MainMenuState::transition_to_game_state() {
        if (gameState == nullptr) {
            cerr << "game state is null" << endl;
        }

        StateMachine::set_state(gameState);
    }
}