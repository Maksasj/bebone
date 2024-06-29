#include "main_menu_state.h"

#include <utility>

#include "../../game.h"
#include "../../rng.h"

namespace game::core::fsm {
    MainMenuState::MainMenuState(shared_ptr<GameObject> flappyBird, const shared_ptr<Input>& input)
        : gameState(nullptr), flappyBird(std::move(flappyBird)), input(input) {

        transitionFunction = std::function<void()>([this]() {
            StateMachine::set_state(gameState);
        });
    }
    
    MainMenuState::~MainMenuState() {
        gameState = nullptr;
        flappyBird = nullptr;
    }

    void MainMenuState::enter() {
        flappyBird->get_transform()->set_position(Vec3f::splat(0.0f));
        flappyBird->get_transform()->set_rotation(0.0f);

        Game::find_game_object_by_name("Pipe1")->get_transform()->set_position(Vec3f(6.2f, Random::rand(-3.0f, 4.5f), 2.0f));
        Game::find_game_object_by_name("Pipe2")->get_transform()->set_position(Vec3f(12.0f, Random::rand(-3.0f, 4.5f), 2.0f));

        input->register_key_action(KeyCode::MouseButtonLeft, transitionFunction);
    }

    void MainMenuState::exit() {
        input->remove_key_action(KeyCode::MouseButtonLeft, transitionFunction);
    }

    void MainMenuState::set_game_state(shared_ptr<State> gameState) {
        this->gameState = std::move(gameState);
    }
}