#include "end_game_state.h"

namespace game::core::fsm {
    EndGameState::EndGameState(shared_ptr<GameObject> flappyBird) : gameState(nullptr), flappyBird(flappyBird) { }

    EndGameState::~EndGameState() {
        gameState = nullptr;
        flappyBird = nullptr;
    }

    void EndGameState::enter() {

    }

    void EndGameState::set_game_state(shared_ptr<State> gameState) {
        this->gameState = gameState;
    }

    void EndGameState::transition_to_game_state() {
        StateMachine::set_state(gameState);
    }
}