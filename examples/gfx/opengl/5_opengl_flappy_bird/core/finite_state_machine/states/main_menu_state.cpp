#include "main_menu_state.h"

#include <utility>

#include "../../game.h"
#include "../../rng.h"

namespace game::core::fsm {
    MainMenuState::MainMenuState(shared_ptr<GameObject> flappy_bird) : game_state(nullptr), flappy_bird(std::move(flappy_bird)) {
        transition_function = std::function < void() > ([this]() {
            StateMachine::set_state(game_state);
        });
    }
    
    MainMenuState::~MainMenuState() {
        game_state = nullptr;
        flappy_bird = nullptr;
    }

    void MainMenuState::enter() {
        flappy_bird->get_transform()->set_position(Vec3f::splat(0.0f));
        flappy_bird->get_transform()->set_rotation(0.0f);

        Game::find_game_object_by_name("Pipe1")->get_transform()->set_position(Vec3f(6.2f, Random::rand(-3.0f, 4.5f), 2.0f));
        Game::find_game_object_by_name("Pipe2")->get_transform()->set_position(Vec3f(12.0f, Random::rand(-3.0f, 4.5f), 2.0f));

        Input::get_instance().register_key_action(KeyCode::MouseButtonLeft, transition_function);
    }

    void MainMenuState::exit() {
        Input::get_instance().remove_key_action(KeyCode::MouseButtonLeft, transition_function);
    }

    void MainMenuState::set_game_state(shared_ptr<State> gameState) {
        this->game_state = std::move(gameState);
    }
}