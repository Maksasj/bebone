#include "bexel.h"

namespace bexel {
    Bexel::Bexel() : window(nullptr), shader(nullptr), world(nullptr) {

    }

    void Bexel::init() {
        BEBONE_PROFILE_RECORD(BEXEL_INIT)

        GLFWContext::init();

        window = WindowFactory::create_window("4. Opengl Bexel example", game_width, game_height, OpenGL, {
            .enable_resize = true
        });

        GLContext::load_opengl();
        glfwSwapInterval(0);

        BEBONE_PROFILE_STOP(BEXEL_INIT)
    }

    void Bexel::load() {
        BEBONE_PROFILE_RECORD(BEXEL_LOAD)

        const auto shader_flags = EnableUniforms;

        auto vertex_shader = GLShaderFactory::create_shader("assets/vertex.glsl", VertexShader, shader_flags);
        auto fragment_shader = GLShaderFactory::create_shader("assets/fragment.glsl", FragmentShader, shader_flags);

        shader = make_unique<GLShaderProgram>(vertex_shader, fragment_shader);

        camera = make_unique<Camera>(Vec3f(0.0, -24.0f, 0.0f), 12);
        world = make_unique<World>();

        texture = make_unique<GLTexture2D>("assets/texture.png");

        BEBONE_PROFILE_STOP(BEXEL_LOAD)
    }

    void Bexel::run() {
        BEBONE_PROFILE_RECORD(BEXEL_RUN)

        GLContext::enable(GL_DEPTH_TEST);

        shader->set_uniform("inTexture", 0);

        while (!window->closing()) {
            BEBONE_PROFILE_RECORD(BEXEL_UPDATE_LOOP)

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

            BEBONE_PROFILE_STOP(BEXEL_UPDATE_LOOP)
        }

        BEBONE_PROFILE_STOP(BEXEL_RUN)
    }

    void Bexel::unload() {
        camera = nullptr;
        world = nullptr;

        shader->destroy();

        GLFWContext::terminate();
    }
}
