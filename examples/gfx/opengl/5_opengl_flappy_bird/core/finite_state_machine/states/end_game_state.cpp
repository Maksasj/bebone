#include "end_game_state.h"

#include <utility>

#include "../../score.h"

namespace game::core::fsm {
    EndGameState::EndGameState(shared_ptr<GameObject> flappyBird) : menuState(nullptr), flappyBird(std::move(flappyBird)) {
        transitionFunction = [this]() {
            StateMachine::set_state(menuState);
        };
    }

    EndGameState::~EndGameState() {
        menuState = nullptr;
        flappyBird = nullptr;
    }

    void EndGameState::enter() {
        cout << "Game Over" << endl;
        cout << "Your score: " << Score::get_score() << endl;

        Input::get_instance().register_key_action(KeyCode::MOUSE_BUTTON_LEFT, transitionFunction);
    }

    void EndGameState::exit() {
        Input::get_instance().remove_key_action(KeyCode::MOUSE_BUTTON_LEFT, transitionFunction);
        Score::clear();
    }

    void EndGameState::set_menu_state(shared_ptr<State> menuState) {
        this->menuState = std::move(menuState);
    }
}