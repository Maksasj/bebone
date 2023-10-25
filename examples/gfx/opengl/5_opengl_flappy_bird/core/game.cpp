#include "game.h"

namespace game::core {
    using namespace bebone::gfx;
    using namespace std;

    Game::Game(const unsigned int& width, const unsigned int& height) {
        const auto aspect = static_cast<f32>(width) / static_cast<f32>(height);

        camera = make_shared<OrthographicCamera>(aspect * -1.0f, aspect * 1.0f, -1.0, 1.0, -1.0f, 1.0f);

        const auto shaderFlags = ENABLE_UNIFORMS;

        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/vertex.glsl", ShaderTypes::VERTEX_SHADER, shaderFlags);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/5_opengl_flappy_bird/fragment.glsl", ShaderTypes::FRAGMENT_SHADER, shaderFlags);
        auto shaderProgram = std::make_shared<GLShaderProgram>(vertexShader, fragmentShader);
        
        auto texture = std::make_shared<GLTexture>("examples/assets/gfx/opengl/5_opengl_flappy_bird/awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

        batch = make_shared<Batch>(shaderProgram, camera, 1024, texture);
    }

    void Game::update() {
        batch->add(Transform());
        batch->add(Transform(Vec3f(-0.5f, -0.5f, 0.0f)));
        batch->render();
    }
}