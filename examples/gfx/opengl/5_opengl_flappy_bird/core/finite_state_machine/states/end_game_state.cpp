#include "end_game_state.h"

#include <utility>

#include "../../score.h"

namespace game::core::fsm {
    EndGameState::EndGameState(shared_ptr<GameObject> flappy_bird) : menu_state(nullptr), flappy_bird(std::move(flappy_bird)) {
        transition_function = [this]() {
            StateMachine::set_state(menu_state);
        };
    }

    EndGameState::~EndGameState() {
        menu_state = nullptr;
        flappy_bird = nullptr;
    }

    void EndGameState::enter() {
        cout << "Game Over" << endl;
        cout << "Your score: " << Score::get_score() << endl;

        Input::get_instance().register_key_action(KeyCode::MouseButtonLeft, transition_function);
    }

    void EndGameState::exit() {
        Input::get_instance().remove_key_action(KeyCode::MouseButtonLeft, transition_function);
        Score::clear();
    }

    void EndGameState::set_menu_state(shared_ptr<State> menuState) {
        this->menu_state = std::move(menuState);
    }
}