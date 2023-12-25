#include "game_state.h"

#include "../../input_system/input.h"

#include "../../entity_component_system/components/flying.h"
#include "../../entity_component_system/components/cyclic_movement.h"

#include "../../game.h"

namespace game::core::fsm {
    using namespace input_system;

    GameState::GameState(shared_ptr<GameObject> flappyBird) : endGameState(nullptr), flappyBird(flappyBird) {
        ground1 = Game::find_game_object_by_name("Ground1");
        ground2 = Game::find_game_object_by_name("Ground2");
        ground3 = Game::find_game_object_by_name("Ground3");
    }

    GameState::~GameState() {
        endGameState = nullptr;
        flappyBird = nullptr;
    }

    void GameState::enter() {
        float flyForce = 0.06f;
        
        auto flying = flappyBird->add_component<Flying>(flyForce);
        flying->set_velocity(flyForce);

        //ground1->add_component<CyclicMovement>();
    }

    void GameState::update() {
        flappyBird->update();
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