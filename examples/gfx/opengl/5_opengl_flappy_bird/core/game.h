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

            shared_ptr<MainMenuState> mainMenuState;
            shared_ptr<GameState> gameState;
            shared_ptr<EndGameState> endGameState;

            static vector<shared_ptr<GameObject>> gameObjects;

            shared_ptr<GameObject> instantiate(const string& gameObjectName, const Vec3f& position = {0.0f, 0.0f, 0.0f});
            void add_renderer_component(shared_ptr<GameObject>& gameObject, const string& textureName, const unsigned int& pixelsPerUnit);
        public:
            Game(const unsigned int& width, const unsigned int& height);
            void update();

            static shared_ptr<GameObject> find_game_object_by_name(const string& gameObjectName);
    };
}

#endif
