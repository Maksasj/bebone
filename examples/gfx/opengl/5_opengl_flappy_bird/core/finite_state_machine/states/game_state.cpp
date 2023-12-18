#include "game_state.h"
#include <iostream>

namespace game::core::fsm {
    GameState::GameState() : endGameState(nullptr) { }

    GameState::~GameState() {
        endGameState = nullptr;
    }

    void GameState::enter() {
        cout << "game state" << endl;
        transition_to_end_game_state();
    }

    void GameState::set_end_game_state(shared_ptr<State> endGameState) {
        this->endGameState = endGameState;
    }

    void GameState::transition_to_end_game_state() {
        if (endGameState == nullptr) {
            cerr << "end game state is null" << endl;
        }

        StateMachine::set_state(endGameState);
    }
}