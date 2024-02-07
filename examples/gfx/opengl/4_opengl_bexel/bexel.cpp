#include "bexel.h"

namespace bexel {
    Bexel::Bexel() : m_window(nullptr), m_shader(nullptr), m_world(nullptr) {

    }

    void Bexel::init() {
        PROFILE_RECORD(BEXEL_INIT)

        GLFWContext::init();

        m_window = WindowFactory::create_window("4. Opengl Bexel example", GAME_WIDTH, GAME_HEIGHT, GfxAPI::OPENGL);

        GLContext::load_opengl();
        glfwSwapInterval(0);

        PROFILE_STOP(BEXEL_INIT)
    }

    void Bexel::load() {
        PROFILE_RECORD(BEXEL_LOAD)

        const auto shaderFlags = ENABLE_UNIFORMS;

        auto vertexShader = GLShaderFactory::create_shader("assets/vertex.glsl", ShaderTypes::VERTEX_SHADER, shaderFlags);
        auto fragmentShader = GLShaderFactory::create_shader("assets/fragment.glsl", ShaderTypes::FRAGMENT_SHADER, shaderFlags);

        m_shader = make_unique<GLShaderProgram>(vertexShader, fragmentShader);

        m_camera = make_unique<Camera>(Vec3f(0.0, -24.0f, 0.0f), 12);
        m_world = make_unique<World>();

        m_texture = make_unique<GLTexture>("assets/texture.png", GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_BYTE);

        PROFILE_STOP(BEXEL_LOAD)
    }

    void Bexel::run() {
        PROFILE_RECORD(BEXEL_RUN)

        GLContext::enable(GL_DEPTH_TEST);
        GLContext::enable(GL_CULL_FACE);
        GLContext::cull_face(GL_BACK);
        GLContext::front_face(GL_CW);

        m_shader->set_uniform("inTexture", 0);

        while (!m_window->closing()) {
            PROFILE_RECORD(BEXEL_UPDATE_LOOP)

            GLContext::set_viewport(0, 0, m_window->get_width(), m_window->get_height());
            GLContext::clear_color(0.47f, 0.65f, 1.0f, 1.0f);
            GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_camera->update(m_window);
            m_world->update(m_camera);

            m_shader->enable();

            m_texture->bind();

            m_camera->bind(m_shader);
            m_world->render(m_shader);

            GLFWContext::swap_buffers(*m_window);
            GLFWContext::poll_events();

            PROFILE_STOP(BEXEL_UPDATE_LOOP)
        }

        PROFILE_STOP(BEXEL_RUN)
    }

    void Bexel::unload() {
        m_camera = nullptr;
        m_world = nullptr;

        m_shader->destroy();

        GLFWContext::terminate();
    }
}
