#include "end_game_state.h"

#include <utility>

#include "../../score.h"
#include "../../input_system/input.h"

namespace game::core::fsm {
    using namespace input_system;

    EndGameState::EndGameState(shared_ptr<GameObject> flappyBird) : menuState(nullptr), flappyBird(std::move(flappyBird)) {
        transitionFunction = make_shared<std::function<void()>>([this]() {
            StateMachine::set_state(menuState);
        });
    }

    EndGameState::~EndGameState() {
        menuState = nullptr;
        flappyBird = nullptr;
    }

    void EndGameState::enter() {
        cout << "Game Over" << endl;
        cout << "Your score: " << Score::get_score() << endl;

        Input::register_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON, transitionFunction);
    }

    void EndGameState::exit() {
        Input::remove_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON, transitionFunction);
        Score::clear();
    }

    void EndGameState::set_menu_state(shared_ptr<State> menuState) {
        this->menuState = std::move(menuState);
    }
}