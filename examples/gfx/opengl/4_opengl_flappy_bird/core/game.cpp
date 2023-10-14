#include "game.h"

namespace game::core {
    using namespace bebone::gfx;
    using namespace std;

    Game::Game(const unsigned int& width, const unsigned int& height) {
        const auto aspect = static_cast<f32>(width) / static_cast<f32>(height);

        camera = make_shared<OrthographicCamera>(aspect * -1.0f, aspect * 1.0f, -1.0, 1.0, -1.0f, 1.0f);

        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/4_opengl_flappy_bird/vertex.shader", ShaderTypes::VERTEX_SHADER);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/4_opengl_flappy_bird/fragment.shader", ShaderTypes::FRAGMENT_SHADER);

        std::shared_ptr<GLShaderProgram> shaderProgram = std::make_shared<GLShaderProgram>(vertexShader, fragmentShader);

        renderer = make_shared<Renderer>(shaderProgram, camera);
    }

    void Game::update(Sprite& sprite) {
        renderer->render(sprite, Transform());
    }
}