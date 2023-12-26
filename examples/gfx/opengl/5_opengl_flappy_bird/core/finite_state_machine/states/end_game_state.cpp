#include "end_game_state.h"

namespace game::core::fsm {
    EndGameState::EndGameState(shared_ptr<GameObject> flappyBird) : menuState(nullptr), flappyBird(flappyBird) { }

    EndGameState::~EndGameState() {
        menuState = nullptr;
        flappyBird = nullptr;
    }

    void EndGameState::enter() {
        cout << "game over" << endl;
    }

    void EndGameState::set_menu_state(shared_ptr<State> menuState) {
        this->menuState = menuState;
    }

    void EndGameState::transition_to_menu_state() {
        StateMachine::set_state(menuState);
    }
}