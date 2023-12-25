#include "game_state.h"

#include "../../input_system/input.h"

#include "../../entity_component_system/components/flying.h"
#include "../../entity_component_system/components/cyclic_movement.h"

#include "../../game.h"

namespace game::core::fsm {
    using namespace input_system;

    #define FLY_FORCE 0.06f

    GameState::GameState(shared_ptr<GameObject> flappyBird) : endGameState(nullptr), flappyBird(flappyBird) {
        ground1 = Game::find_game_object_by_name("Ground1");
        ground2 = Game::find_game_object_by_name("Ground2");
        ground3 = Game::find_game_object_by_name("Ground3");
        pipe1 = Game::find_game_object_by_name("Pipe1");
        pipe2 = Game::find_game_object_by_name("Pipe2");

        auto sprite = ground2->get_component<SpriteRenderer>()->get_sprite();

        float endPoint = ground2->get_transform()->get_position().x;
        endPoint -= 5.21f; // offset

        float startPoint = ground3->get_transform()->get_position().x;
        startPoint += 5.21f; // offset

        ground1->add_component<CyclicMovement>(endPoint, startPoint);
        ground2->add_component<CyclicMovement>(endPoint, startPoint);
        ground3->add_component<CyclicMovement>(endPoint, startPoint);

        pipe1->add_component<CyclicMovement>(-6.2f, 6.2f, true);
        pipe2->add_component<CyclicMovement>(-6.2f, 6.2f, true);

        flappyBird->add_component<Flying>(FLY_FORCE);
    }

    GameState::~GameState() {
        endGameState = nullptr;
        flappyBird = nullptr;
    }

    void GameState::enter() {
        auto flying = flappyBird->get_component<Flying>();
        flying->set_velocity(FLY_FORCE);
        flying->enable();

        ground1->get_component<CyclicMovement>()->enable();
        ground2->get_component<CyclicMovement>()->enable();
        ground3->get_component<CyclicMovement>()->enable();
        pipe1->get_component<CyclicMovement>()->enable();
        pipe2->get_component<CyclicMovement>()->enable();
    }

    void GameState::update() {
        flappyBird->update();
        ground1->update();
        ground2->update();
        ground3->update();
        pipe1->update();
        pipe2->update();
    }

    void GameState::exit() {
        
    }

    void GameState::set_end_game_state(shared_ptr<State> endGameState) {
        this->endGameState = endGameState;
    }

    void GameState::transition_to_end_game_state() {
        StateMachine::set_state(endGameState);
    }
}