#include "end_game_state.h"

#include "../../score.h"

#include "../../input_system/input.h"
#include "../../input_system/action.h"
#include "../../input_system/key_codes.h"

namespace game::core::fsm {
    using namespace input_system;

    EndGameState::EndGameState(shared_ptr<GameObject> flappyBird) : menuState(nullptr), flappyBird(flappyBird) { }

    EndGameState::~EndGameState() {
        menuState = nullptr;
        flappyBird = nullptr;
    }

    void EndGameState::enter() {
        cout << "Game Over" << endl;
        cout << "Your score: " << Score::get_score() << endl;

        auto enterMenuFuction = [this]() {
            transition_to_menu_state();
        };
        Input::register_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON, Action(enterMenuFuction));
    }

    void EndGameState::exit() {
        Input::remove_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON);
        Score::clear();
    }

    void EndGameState::set_menu_state(shared_ptr<State> menuState) {
        this->menuState = menuState;
    }

    void EndGameState::transition_to_menu_state() {
        StateMachine::set_state(menuState);
    }
}