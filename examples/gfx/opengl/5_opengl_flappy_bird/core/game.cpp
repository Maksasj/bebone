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

        camera = make_shared<OrthographicCamera>(aspect * -7.0f, aspect * 7.0f, 7.0, -7.0, -7.0f, 7.0f);
 
        const auto shaderFlags = ENABLE_UNIFORMS;

        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/vertex.glsl", ShaderTypes::VERTEX_SHADER, shaderFlags);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/fragment.glsl", ShaderTypes::FRAGMENT_SHADER, shaderFlags);
        auto shaderProgram = make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        TextureLoader::load_textures("examples\\assets\\gfx\\opengl\\5_opengl_flappy_bird\\gfx\\");
        
        batch = make_shared<Batch>(shaderProgram, camera, 1024);

        auto bg = create_game_object_with_renderer("Background", "bg");
        bg->get_transform()->set_scale(0.6f);
        batch->add(bg);

        auto flappyBird = create_game_object_with_renderer("Flappy Bird", "flappy_bird");
        batch->add(flappyBird);
        
        auto ground = create_game_object_with_renderer("Ground", "ground");
        batch->add(ground);
        auto& groundTransform = ground->get_transform();
        groundTransform->set_scale(0.5f);
        groundTransform->set_position(Vec2f(0, -7.0f));

        mainMenuState = make_shared<MainMenuState>(flappyBird);
        gameState = make_shared<GameState>(flappyBird);
        endGameState = make_shared<EndGameState>(flappyBird);
        
        mainMenuState->set_game_state(gameState);
        gameState->set_end_game_state(endGameState);
        endGameState->set_game_state(gameState);

        StateMachine::set_state(mainMenuState);
    }

    shared_ptr<GameObject> Game::create_game_object_with_renderer(const string& gameObjectName, const string& textureName) {
        auto gameObject = make_shared<GameObject>(gameObjectName);
        auto sprite = make_shared<Sprite>(textureName);
        auto renderer = make_shared<SpriteRenderer>(sprite);
        gameObject->add_component(renderer);

        return gameObject;
    }

    void Game::update() {
        Input::execute_pooled_actions();

        StateMachine::update_current_state();

        batch->render();
    }
}