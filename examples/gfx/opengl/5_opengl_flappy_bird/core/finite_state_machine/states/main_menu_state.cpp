#include "main_menu_state.h"
#include "../../input_system/input.h"

namespace game::core::fsm {
    using namespace input_system;

    MainMenuState::MainMenuState(shared_ptr<GameObject> flappyBird) : gameState(nullptr), flappyBird(flappyBird) { }
    
    MainMenuState::~MainMenuState() {
        gameState = nullptr;
        flappyBird = nullptr;
    }

    void MainMenuState::enter() {
        auto clickToStartFunction = [this]() {
            transition_to_game_state();
        };

        Input::register_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON, Action(clickToStartFunction));
    }

    void MainMenuState::exit() {
        Input::remove_mouse_action(MouseKeyCode::LEFT_MOUSE_BUTTON);
    }

    void MainMenuState::set_game_state(shared_ptr<State> gameState) {
        this->gameState = gameState;
    }

    void MainMenuState::transition_to_game_state() {
        StateMachine::set_state(gameState);
    }
}