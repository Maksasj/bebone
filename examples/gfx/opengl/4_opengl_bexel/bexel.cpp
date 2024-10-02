#include "bexel.h"

namespace bexel {
    Bexel::Bexel() : window(nullptr), shader(nullptr), world(nullptr) {

    }

    void Bexel::init() {
        window = WindowFactory::create_window("4. Opengl Bexel example", game_width, game_height, OpenGL, {
            .enable_resize = true
        });

        GLContext::load_opengl();
        glfwSwapInterval(0);
    }

    void Bexel::load() {
        const auto shader_flags = EnableUniforms;

        auto vertex_shader = GLShaderFactory::create_shader("assets/vertex.glsl", ShaderType::VertexShader, shader_flags);
        auto fragment_shader = GLShaderFactory::create_shader("assets/fragment.glsl", ShaderType::FragmentShader, shader_flags);

        shader = make_unique<GLShaderProgram>(vertex_shader, fragment_shader);

        camera = make_unique<Camera>(Vec3f(0.0, -24.0f, 0.0f), 12);
        world = make_unique<World>();

        texture = make_unique<GLTexture2D>("assets/texture.png");
    }

    void Bexel::run() {
        shader->set_uniform("inTexture", 0);

        while (!window->closing()) {
            GLContext::set_viewport(0, 0, window->get_width(), window->get_height());
            GLContext::clear_color(0.47f, 0.65f, 1.0f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            camera->update(window);
            world->update(camera);

            shader->enable();

            texture->bind();

            camera->bind(shader);
            world->render(shader);

            GLFWContext::swap_buffers(*window);
            window->pull_events();
        }
    }

    void Bexel::unload() {
        camera = nullptr;
        world = nullptr;

        shader->destroy();
    }
}
