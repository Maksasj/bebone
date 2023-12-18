#include "end_game_state.h"
#include <iostream>

namespace game::core::fsm {
    EndGameState::EndGameState() : gameState(nullptr) { }

    EndGameState::~EndGameState() {
        gameState = nullptr;
    }

    void EndGameState::enter() {
        cout << "end game state" << endl;
    }

    void EndGameState::set_game_state(shared_ptr<State> gameState) {
        this->gameState = gameState;
    }

    void EndGameState::transition_to_game_state() {
        if (gameState == nullptr) {
            cerr << "game state is null" << endl;
        }

        StateMachine::set_state(gameState);
    }
}