#include "main_menu_state.h"
#include "../../input_system/input.h"

#include "../../game.h"
#include "../../rng.h"

namespace game::core::fsm {
    using namespace input_system;

    MainMenuState::MainMenuState(shared_ptr<GameObject> flappyBird) : gameState(nullptr), flappyBird(flappyBird) { }
    
    MainMenuState::~MainMenuState() {
        gameState = nullptr;
        flappyBird = nullptr;
    }

    void MainMenuState::enter() {
        flappyBird->get_transform()->set_position(Vec3f(0.0f, 0.0f, 0.0f));
        flappyBird->get_transform()->set_rotation(0.0f);

        Game::find_game_object_by_name("Pipe1")->get_transform()->set_position(Vec3f(6.2f, Random::rand(-3.0f, 4.5f), 2.0f));
        Game::find_game_object_by_name("Pipe2")->get_transform()->set_position(Vec3f(12.0f, Random::rand(-3.0f, 4.5f), 2.0f));

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