#include "game.h"
#include "texture_loader.h"
#include "entity_component_system/components/sprite_renderer.h"
#include "entity_component_system/game_object.h"
#include "input_system/input.h"

namespace game::core {
    using namespace bebone::gfx;
    using namespace std;
    using namespace ecs;
    using namespace fsm;
    using namespace input_system;

    Game::Game(const unsigned int& width, const unsigned int& height) {
        const auto aspect = static_cast<f32>(width) / static_cast<f32>(height);

        camera = make_shared<OrthographicCamera>(aspect * -5.0f, aspect * 5.0f, 5.0, -5.0, -5.0f, 5.0f);
 
        const auto shaderFlags = ENABLE_UNIFORMS;

        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/vertex.glsl", ShaderTypes::VERTEX_SHADER, shaderFlags);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/fragment.glsl", ShaderTypes::FRAGMENT_SHADER, shaderFlags);
        auto shaderProgram = make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        TextureLoader::load_textures("examples\\assets\\gfx\\opengl\\5_opengl_flappy_bird\\gfx\\");
        
        batch = make_shared<Batch>(shaderProgram, camera, 1024);

        auto sprite = make_shared<Sprite>("flappy_bird");
        auto gameObject = make_shared<GameObject>("Flappy Bird");
        auto renderer = make_shared<SpriteRenderer>(sprite);
        gameObject->add_component(renderer);
        batch->add(gameObject);

        mainMenuState = make_shared<MainMenuState>(gameObject);
        gameState = make_shared<GameState>(gameObject);
        endGameState = make_shared<EndGameState>(gameObject);
        
        mainMenuState->set_game_state(gameState);
        gameState->set_end_game_state(endGameState);
        endGameState->set_game_state(gameState);

        StateMachine::set_state(mainMenuState);
    }

    void Game::update() {
        Input::execute_pooled_actions();

        StateMachine::update_current_state();

        batch->render();
    }
}