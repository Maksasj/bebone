#include "game.h"
#include "texture_loader.h"
#include "entity_component_system/components/sprite_renderer.h"
#include "entity_component_system/game_object.h"

#include "rng.h"

namespace game::core {
    using namespace bebone::gfx;
    using namespace std;
    using namespace ecs;
    using namespace fsm;

    vector<shared_ptr<GameObject>> Game::gameObjects = vector<shared_ptr<GameObject>>();

    Game::Game(const unsigned int& width, const unsigned int& height) {
        const auto aspect = static_cast<f32>(width) / static_cast<f32>(height);

        camera = make_shared<OrthographicCamera>(aspect * -7.0f, aspect * 7.0f, 7.0, -7.0, -7.0f, 7.0f);
 
        const auto shaderFlags = EnableUniforms;

        auto vertexShader = GLShaderFactory::create_shader("assets/vertex.glsl", ShaderTypes::VERTEX_SHADER, shaderFlags);
        auto fragmentShader = GLShaderFactory::create_shader("assets/fragment.glsl", ShaderTypes::FRAGMENT_SHADER, shaderFlags);
        auto shaderProgram = make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        TextureLoader::load_textures("assets/gfx");
        
        batch = make_shared<Batch>(shaderProgram, camera, 1024);

        auto bg = instantiate("Background", Vec3f(0.0f, 0.0f, 3.0f));
        add_renderer_component(bg, "bg", 32);
        bg->get_transform()->set_scale(0.6f);
        batch->add(bg);

        auto flappyBird = instantiate("Flappy Bird");
        add_renderer_component(flappyBird, "flappy_bird", 32);
        batch->add(flappyBird);
        
        auto ground1 = instantiate("Ground1", Vec3f(0, -7.0f, 1.0f));
        auto ground1Transform = ground1->get_transform();
        add_renderer_component(ground1, "ground", 32);
        batch->add(ground1);
        ground1Transform->set_scale(0.5f);

        auto groundSprite = ground1->get_component<SpriteRenderer>()->get_sprite();

        Vec3f ground2Position = ground1Transform->get_position();
        ground2Position.x = groundSprite->get_unit_width();

        auto ground2 = instantiate("Ground2", ground2Position);
        add_renderer_component(ground2, "ground", 32);
        batch->add(ground2);
        ground2->get_transform()->set_scale(0.5f);

        auto pipe1 = instantiate("Pipe1");
        add_renderer_component(pipe1, "pipes", 32);
        batch->add(pipe1);
        pipe1->get_transform()->set_scale(0.5f);

        auto pipe2 = instantiate("Pipe2");
        add_renderer_component(pipe2, "pipes", 32);
        batch->add(pipe2);
        pipe2->get_transform()->set_scale(0.5f);

        mainMenuState = make_shared<MainMenuState>(flappyBird);
        gameState = make_shared<GameState>(flappyBird);
        endGameState = make_shared<EndGameState>(flappyBird);
        
        mainMenuState->set_game_state(gameState);
        gameState->set_end_game_state(endGameState);
        endGameState->set_menu_state(mainMenuState);

        StateMachine::set_state(mainMenuState);
    }

    shared_ptr<GameObject> Game::instantiate(const string& gameObjectName, const Vec3f& position) {
        auto gameObject = make_shared<GameObject>(gameObjectName, position);
        gameObjects.push_back(gameObject);

        return gameObject;
    }

    void Game::add_renderer_component(shared_ptr<GameObject>& gameObject, const string& textureName, const unsigned int& pixelsPerUnit) {
        auto sprite = make_shared<Sprite>(textureName, pixelsPerUnit);
        gameObject->add_component<SpriteRenderer>(sprite);
    }

    void Game::update() {
        StateMachine::update_current_state();
        update_game_objects();

        batch->render();
    }

    void Game::update_game_objects() {
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
            (*it)->update();
        }
    }

    shared_ptr<GameObject> Game::find_game_object_by_name(const string& gameObjectName) {
        for (auto it = gameObjects.begin(); it != gameObjects.end(); ++it) {
            auto gameObject = *it;

            if (gameObject->get_name() == gameObjectName) {
                return gameObject;
            }
        }
        
        return nullptr;
    }
}