#include "game.h"

namespace game::core {
    Game::Game(const unsigned int& width, const unsigned int& height) : camera(0.0f, width, height, 0, -1.0f, 1.0f) {
        using namespace bebone::gfx;

        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/3_opengl_3d_cube/vertex.shader", ShaderTypes::VERTEX_SHADER);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/3_opengl_3d_cube/fragment.shader", ShaderTypes::FRAGMENT_SHADER);
        std::shared_ptr<GLShaderProgram> shaderProgram = std::make_shared<GLShaderProgram>(vertexShader, fragmentShader);
        renderer = std::make_shared<Renderer>(shaderProgram, camera);
    }

    void Game::update(GLTexture& texture) {
        renderer->render(texture, Transform());
    }
}