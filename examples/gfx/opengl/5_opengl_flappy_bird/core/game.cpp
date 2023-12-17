#include "game.h"
#include "texture_loader.h"
#include "entity_component_system/components/sprite_renderer.h"
#include "entity_component_system/game_object.h"

namespace game::core {
    using namespace bebone::gfx;
    using namespace std;
    using namespace ecs;

    Game::Game(const unsigned int& width, const unsigned int& height) {
        const auto aspect = static_cast<f32>(width) / static_cast<f32>(height);

        camera = make_shared<OrthographicCamera>(aspect * -1.0f, aspect * 1.0f, 1.0, -1.0, -1.0f, 1.0f);

        const auto shaderFlags = ENABLE_UNIFORMS;

        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/vertex.glsl", ShaderTypes::VERTEX_SHADER, shaderFlags);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/fragment.glsl", ShaderTypes::FRAGMENT_SHADER, shaderFlags);
        auto shaderProgram = make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        TextureLoader::load_textures("examples\\assets\\gfx\\opengl\\5_opengl_flappy_bird\\gfx\\");

        batch = make_shared<Batch>(shaderProgram, camera, 1024);

        player1 = make_shared<GameObject>();
        player2 = make_shared<GameObject>();
        auto flappyBird = make_shared<Sprite>("flappy_bird");
        auto spriteRenderer1 = make_shared<SpriteRenderer>(flappyBird);
        auto spriteRenderer2 = make_shared<SpriteRenderer>(flappyBird);

        player1->add_component(spriteRenderer1);
        player2->add_component(spriteRenderer2);

        batch->add(player1, spriteRenderer1);
        batch->add(player2, spriteRenderer2);

        player2->get_transform().set_position(Vec3f(1.0f, 0.75f, 0.0f));
        player2->get_transform().set_scale(0.5f);
    }

    void Game::update() {
        batch->render();
    }
}