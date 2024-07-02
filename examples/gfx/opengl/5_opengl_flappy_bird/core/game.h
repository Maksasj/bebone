#ifndef _GAME_H_
#define _GAME_H_

#include <memory>
#include <string>
#include <vector>

#include "bebone/bebone.h"
#include "game_time.h"
#include "batch.h"
#include "sprite.h"

#include "entity_component_system/game_object.h"

#include "finite_state_machine/state_machine.h"
#include "finite_state_machine/states/main_menu_state.h"
#include "finite_state_machine/states/game_state.h"
#include "finite_state_machine/states/end_game_state.h"

namespace game::core {
    using namespace std;
    using namespace fsm;
    using namespace ecs;

    class Game : private bebone::core::NonCopyable {
        private:
            shared_ptr<Batch> batch;
            shared_ptr<OrthographicCamera> camera;

            shared_ptr<MainMenuState> main_menu_state;
            shared_ptr<GameState> game_state;
            shared_ptr<EndGameState> end_game_state;

            shared_ptr<Input> input;

            static vector<shared_ptr<GameObject>> game_objects;

            shared_ptr<GameObject> instantiate(const string& game_object_name, const Vec3f& position = {0.0f, 0.0f, 0.0f});
            void add_renderer_component(shared_ptr<GameObject>& game_object, const string& texture_name, const unsigned int& pixels_per_unit);

            void update_game_objects();
        public:
            Game(const unsigned int& width, const unsigned int& height, const shared_ptr<Input>& input);
            void update();

            static shared_ptr<GameObject> find_game_object_by_name(const string& game_object_name);
    };
}

#endif
