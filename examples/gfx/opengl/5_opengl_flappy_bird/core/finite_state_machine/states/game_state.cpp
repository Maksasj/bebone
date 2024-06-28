#include "game_state.h"

#include <utility>

#include "../../entity_component_system/components/flying.h"
#include "../../entity_component_system/components/cyclic_movement.h"
#include "../../entity_component_system/components/collider.h"

#include "../../game.h"
#include "../../score.h"

namespace game::core::fsm {
    #define FLY_FORCE 0.06f

    GameState::GameState(const shared_ptr<GameObject>& flappy_bird) : end_game_state(nullptr), flappy_bird(flappy_bird) {
        ground1 = Game::find_game_object_by_name("Ground1");
        ground2 = Game::find_game_object_by_name("Ground2");
        pipe1 = Game::find_game_object_by_name("Pipe1");
        pipe2 = Game::find_game_object_by_name("Pipe2");

        auto ground_sprite = ground2->get_component<SpriteRenderer>()->get_sprite();

        float end_point = -ground_sprite->get_unit_width() + 0.05f;
        float start_point = -end_point;

        ground1->add_component<CyclicMovement>(end_point, start_point)->disable();
        ground2->add_component<CyclicMovement>(end_point, start_point)->disable();

        pipe1->add_component<CyclicMovement>(-6.2f, 6.2f, true)->disable();
        pipe2->add_component<CyclicMovement>(-6.2f, 6.2f, true)->disable();
        
        auto pipe_sprite = pipe1->get_component<SpriteRenderer>()->get_sprite();
        float empty_space = 1.45f; // hardcoded value
        Vec2f top_pipe_collider_top_left_point = { -pipe_sprite->get_unit_width() / 2.0f, pipe_sprite->get_unit_height() / 2.0f };
        Vec2f top_pipe_collider_bottom_right_point = { pipe_sprite->get_unit_width() / 2.0f, empty_space };
        pipe1->add_component<Collider>(top_pipe_collider_top_left_point, top_pipe_collider_bottom_right_point);
        pipe2->add_component<Collider>(top_pipe_collider_top_left_point, top_pipe_collider_bottom_right_point);
        
        Vec2f bottom_pipe_collider_top_left_point = { -pipe_sprite->get_unit_width() / 2.0f, -empty_space };
        Vec2f bottom_pipe_collider_bottom_right_point = { pipe_sprite->get_unit_width() / 2.0f, -pipe_sprite->get_unit_height() / 2.0f };
        pipe1->add_component<Collider>(bottom_pipe_collider_top_left_point, bottom_pipe_collider_bottom_right_point);
        pipe2->add_component<Collider>(bottom_pipe_collider_top_left_point, bottom_pipe_collider_bottom_right_point);
        
        Vec2f empty_space_trigger_top_left_point = { -pipe_sprite->get_unit_width() / 3.5f, empty_space };
        Vec2f empty_space_trigger_bottom_right_point = { pipe_sprite->get_unit_width() / 3.5f, -empty_space };
        pipe1->add_component<Collider>(empty_space_trigger_top_left_point, empty_space_trigger_bottom_right_point, true);
        pipe2->add_component<Collider>(empty_space_trigger_top_left_point, empty_space_trigger_bottom_right_point, true);

        flappy_bird->add_component<Flying>(FLY_FORCE)->disable();
        
        auto flappy_bird_sprite = flappy_bird->get_component<SpriteRenderer>()->get_sprite();
        Vec2f flappy_bird_collider_top_left_point = { -flappy_bird_sprite->get_unit_width() / 2.0f, flappy_bird_sprite->get_unit_height() / 2.0f };
        Vec2f flappy_bird_collider_bottom_right_point = { flappy_bird_sprite->get_unit_width() / 2.0f, -flappy_bird_sprite->get_unit_height() / 2.0f};
        flappy_bird->add_component<Collider>(flappy_bird_collider_top_left_point, flappy_bird_collider_bottom_right_point);

        ground_y = ground1->get_transform()->get_position().y + ground_sprite->get_unit_height() / 2;
        air_y = -(ground1->get_transform()->get_position().y - ground_sprite->get_unit_height() / 2) - 0.1f;
    }

    GameState::~GameState() {
        end_game_state = nullptr;
        flappy_bird = nullptr;
    }

    void GameState::enter() {
        auto flying = flappy_bird->get_component<Flying>();
        flying->set_velocity(FLY_FORCE);
        flying->enable();

        ground1->get_component<CyclicMovement>()->enable();
        ground2->get_component<CyclicMovement>()->enable();

        pipe1->get_component<CyclicMovement>()->enable();
        pipe2->get_component<CyclicMovement>()->enable();
    }

    void GameState::update() {
        if (flappy_bird->get_transform()->get_position().y <= ground_y) {
            transition_to_end_game_state();
        }
        
        if (flappy_bird->get_transform()->get_position().y >= air_y) {
            transition_to_end_game_state();
        }
        
        if (pipe_player_collision_check(pipe1) || pipe_player_collision_check(pipe2)) {
            transition_to_end_game_state();
        }
    }

    bool GameState::pipe_player_collision_check(shared_ptr<GameObject> game_object) const {
        auto obj_colliders = game_object->get_components<Collider>();
        auto obj_transform = game_object->get_transform();

        auto player_collider = flappy_bird->get_component<Collider>();
        auto player_transform = flappy_bird->get_transform();

        Vec2f player_top_left = player_collider->get_top_left() + player_transform->get_position();
        Vec2f player_bottom_right = player_collider->get_bottom_right() + player_transform->get_position();
        
        for (const auto& collider : obj_colliders) {
            Vec2f obj_top_left = collider->get_top_left() + obj_transform->get_position();
            Vec2f obj_bottom_right = collider->get_bottom_right() + obj_transform->get_position();

            bool collision = obj_top_left.x <= player_bottom_right.x &&
                obj_bottom_right.x >= player_top_left.x &&
                obj_top_left.y >= player_bottom_right.y &&
                obj_bottom_right.y <= player_top_left.y;

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
        flappy_bird->get_component<Flying>()->disable();
        ground1->get_component<CyclicMovement>()->disable();
        ground2->get_component<CyclicMovement>()->disable();
        pipe1->get_component<CyclicMovement>()->disable();
        pipe2->get_component<CyclicMovement>()->disable();
    }

    void GameState::set_end_game_state(shared_ptr<State> endGameState) {
        this->end_game_state = std::move(endGameState);
    }

    void GameState::transition_to_end_game_state() {
        StateMachine::set_state(end_game_state);
    }
}