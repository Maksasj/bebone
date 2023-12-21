#include "game_state.h"

#include "../../input_system/input.h"
#include "../../entity_component_system/components/flying.h"

namespace game::core::fsm {
    using namespace input_system;

    GameState::GameState(shared_ptr<GameObject> flappyBird) : endGameState(nullptr), flappyBird(flappyBird) { }

    GameState::~GameState() {
        endGameState = nullptr;
        flappyBird = nullptr;
    }

    void GameState::enter() {
        float flyForce = 0.06f;
        auto flying = make_shared<Flying>(flappyBird->get_transform(), flyForce);
        flappyBird->add_component(flying);
        flying->set_velocity(flyForce);
        flappyBird->update();
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