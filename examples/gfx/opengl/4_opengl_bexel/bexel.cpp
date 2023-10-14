#include "bexel.h"

namespace bexel {
    Bexel::Bexel() : m_window(nullptr), m_shader(nullptr), m_world(nullptr) {

    }

    void Bexel::init() {
        glfwInit();

        m_window = WindowFactory::create_window("4. Bexel example", GAME_WIDTH, GAME_HEIGHT, GfxAPI::OPENGL);

        gladLoadGL();
        glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);
        glfwSwapInterval(0);
    }

    void Bexel::load() {
        auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/4_opengl_bexel/vertex.shader", ShaderTypes::VERTEX_SHADER);
        auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/4_opengl_bexel/fragment.shader", ShaderTypes::FRAGMENT_SHADER);

        m_shader = make_unique<GLShaderProgram>(vertexShader, fragmentShader);
        m_world = make_unique<World>();
    }

    void Bexel::run() {
        glEnable(GL_DEPTH_TEST);

        Chunk chunk(Vec3f::splat(0.0f));

        while (!m_window->closing()) {
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            m_shader->enable();

            chunk.render(m_shader);

            // m_world->render(m_shader);

            glfwSwapBuffers(m_window->get_backend());
            glfwPollEvents();
        }
    }

    void Bexel::unload() {
        m_world = nullptr;

        m_shader->destroy();

        glfwTerminate();
    }
}
