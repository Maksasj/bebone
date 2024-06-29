#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <memory>

#include "state.h"
#include "../state_machine.h"

#include "../../entity_component_system/game_object.h"

namespace game::core::fsm {
    using namespace std;
    using namespace ecs;

    class GameState : public State {
        private:
            shared_ptr<State> end_game_state;
            shared_ptr<GameObject> flappy_bird;
            
            shared_ptr<GameObject> ground1;
            shared_ptr<GameObject> ground2;
            shared_ptr<GameObject> pipe1;
            shared_ptr<GameObject> pipe2;

            float ground_y;
            float air_y;

            bool pipe_player_collision_check(shared_ptr<GameObject> game_object) const;

            void transition_to_end_game_state();
        public:
            explicit GameState(const shared_ptr<GameObject>& flappy_bird);
            ~GameState() override;

            void enter() override;
            void update() override;
            void exit() override;

            void set_end_game_state(shared_ptr<State> end_game_state);

    };
}

#endif
