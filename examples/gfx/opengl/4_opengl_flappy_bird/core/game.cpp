#include "game.h"

namespace game::core {
    Game::Game(const unsigned int& width, const unsigned int& height) : camera(0.0f, width, height, 0, -1.0f, 1.0f) {
        using namespace bebone::gfx;

        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/3_opengl_3d_cube/vertex.shader", ShaderTypes::VERTEX_SHADER);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/3_opengl_3d_cube/fragment.shader", ShaderTypes::FRAGMENT_SHADER);
        GLShaderProgram shaderProgram(vertexShader, fragmentShader);

        renderer = Renderer(shaderProgram, camera);
    }

    void Game::update() {

    }
}