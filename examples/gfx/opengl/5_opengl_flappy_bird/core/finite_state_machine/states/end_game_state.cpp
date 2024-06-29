#include "end_game_state.h"

#include <utility>

#include "../../score.h"

namespace game::core::fsm {
    EndGameState::EndGameState(shared_ptr<GameObject> flappyBird, const shared_ptr<Input>& input) : menuState(nullptr), flappyBird(std::move(flappyBird)), input(input) {
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

        input->register_key_action(KeyCode::MouseButtonLeft, transitionFunction);
    }

    void EndGameState::exit() {
        input->remove_key_action(KeyCode::MouseButtonLeft, transitionFunction);
        Score::clear();
    }

    void EndGameState::set_menu_state(shared_ptr<State> menuState) {
        this->menuState = std::move(menuState);
    }
}