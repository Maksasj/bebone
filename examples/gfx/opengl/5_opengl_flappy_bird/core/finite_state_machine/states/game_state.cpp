#include "game_state.h"

#include "../../input_system/input.h"

#include "../../entity_component_system/components/flying.h"
#include "../../entity_component_system/components/cyclic_movement.h"
#include "../../entity_component_system/components/collider.h"

#include "../../game.h"
#include "../../score.h"

namespace game::core::fsm {
    using namespace input_system;

    #define FLY_FORCE 0.06f

    GameState::GameState(shared_ptr<GameObject> flappyBird) : endGameState(nullptr), flappyBird(flappyBird) {
        ground1 = Game::find_game_object_by_name("Ground1");
        ground2 = Game::find_game_object_by_name("Ground2");
        ground3 = Game::find_game_object_by_name("Ground3");
        pipe1 = Game::find_game_object_by_name("Pipe1");
        pipe2 = Game::find_game_object_by_name("Pipe2");

        auto groundSprite = ground2->get_component<SpriteRenderer>()->get_sprite();

        float endPoint = -groundSprite->get_unit_width() + 0.05f;
        float startPoint = -endPoint;

        ground1->add_component<CyclicMovement>(endPoint, startPoint)->disable();
        ground2->add_component<CyclicMovement>(endPoint, startPoint)->disable();
        ground3->add_component<CyclicMovement>(endPoint, startPoint)->disable();

        pipe1->add_component<CyclicMovement>(-6.2f, 6.2f, true)->disable();
        pipe2->add_component<CyclicMovement>(-6.2f, 6.2f, true)->disable();
        
        auto pipeSprite = pipe1->get_component<SpriteRenderer>()->get_sprite();
        float emptySpace = 1.45f; // hardcoded value
        Vec2f topPipeColliderTopLeftPoint = { -pipeSprite->get_unit_width() / 2.0f, pipeSprite->get_unit_height() / 2.0f };
        Vec2f topPipeColliderBottomRightPoint = { pipeSprite->get_unit_width() / 2.0f, emptySpace };
        pipe1->add_component<Collider>(topPipeColliderTopLeftPoint, topPipeColliderBottomRightPoint);
        pipe2->add_component<Collider>(topPipeColliderTopLeftPoint, topPipeColliderBottomRightPoint);
        
        Vec2f bottomPipeColliderTopLeftPoint = { -pipeSprite->get_unit_width() / 2.0f, -emptySpace };
        Vec2f bottomPipeColliderBottomRightPoint = { pipeSprite->get_unit_width() / 2.0f, -pipeSprite->get_unit_height() / 2.0f };
        pipe1->add_component<Collider>(bottomPipeColliderTopLeftPoint, bottomPipeColliderBottomRightPoint);
        pipe2->add_component<Collider>(bottomPipeColliderTopLeftPoint, bottomPipeColliderBottomRightPoint);
        
        Vec2f emptySpaceTriggerTopLeftPoint = { -pipeSprite->get_unit_width() / 3.5f, emptySpace };
        Vec2f emptySpaceTriggerBottomRightPoint = { pipeSprite->get_unit_width() / 3.5f, -emptySpace };
        pipe1->add_component<Collider>(emptySpaceTriggerTopLeftPoint, emptySpaceTriggerBottomRightPoint, true);
        pipe2->add_component<Collider>(emptySpaceTriggerTopLeftPoint, emptySpaceTriggerBottomRightPoint, true);

        flappyBird->add_component<Flying>(FLY_FORCE)->disable();
        
        auto flappyBirdSprite = flappyBird->get_component<SpriteRenderer>()->get_sprite();
        Vec2f flappyBirdColliderTopLeftPoint = { -flappyBirdSprite->get_unit_width() / 2.0f, flappyBirdSprite->get_unit_height() / 2.0f };
        Vec2f flappyBirdColliderBottomRightPoint = { flappyBirdSprite->get_unit_width() / 2.0f, -flappyBirdSprite->get_unit_height() / 2.0f};
        flappyBird->add_component<Collider>(flappyBirdColliderTopLeftPoint, flappyBirdColliderBottomRightPoint);

        groundY = ground1->get_transform()->get_position().y + groundSprite->get_unit_height() / 2;
        airY = -(ground1->get_transform()->get_position().y - groundSprite->get_unit_height() / 2) - 0.1f;
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
        if (flappyBird->get_transform()->get_position().y <= groundY) {
            transition_to_end_game_state();
        }
        
        if (flappyBird->get_transform()->get_position().y >= airY) {
            transition_to_end_game_state();
        }
        
        if (pipe_player_collision_check(pipe1) || pipe_player_collision_check(pipe2)) {
            transition_to_end_game_state();
        }
    }

    bool GameState::pipe_player_collision_check(shared_ptr<GameObject> gameObject) const {
        auto objColliders = gameObject->get_components<Collider>();
        auto objTransform = gameObject->get_transform();

        auto playerCollider = flappyBird->get_component<Collider>();
        auto playerTransform = flappyBird->get_transform();

        Vec2f playerTopLeft = playerCollider->get_top_left() + playerTransform->get_position();
        Vec2f playerBottomRight = playerCollider->get_bottom_right() + playerTransform->get_position();
        
        for (auto it = objColliders.begin(); it != objColliders.end(); ++it) {
            auto collider = *it;

            Vec2f objTopLeft = collider->get_top_left() + objTransform->get_position();
            Vec2f objBottomRight = collider->get_bottom_right() + objTransform->get_position();

            bool collision = objTopLeft.x <= playerBottomRight.x &&
                objBottomRight.x >= playerTopLeft.x &&
                objTopLeft.y >= playerBottomRight.y &&
                objBottomRight.y <= playerTopLeft.y;

            if (collision && collider->is_trigger() && !collider->is_triggered()) {
                collider->enter_trigger();
                Score::increment();
            } else if (!collision && collider->is_trigger() && collider->is_triggered()) {
                collider->exit_trigger();
            } else if (collision && !collider->is_trigger()) {
                return true;
            }
        }

        return false;
    }

    void GameState::exit() {
        flappyBird->get_component<Flying>()->disable();
        ground1->get_component<CyclicMovement>()->disable();
        ground2->get_component<CyclicMovement>()->disable();
        ground3->get_component<CyclicMovement>()->disable();
        pipe1->get_component<CyclicMovement>()->disable();
        pipe2->get_component<CyclicMovement>()->disable();
    }

    void GameState::set_end_game_state(shared_ptr<State> endGameState) {
        this->endGameState = endGameState;
    }

    void GameState::transition_to_end_game_state() {
        StateMachine::set_state(endGameState);
    }
}