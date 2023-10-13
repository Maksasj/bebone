#ifndef BEXEL_H
#define BEXEL_H

#include "world.h"

namespace bexel {
    static const u64 GAME_WIDTH = 800;
    static const u64 GAME_HEIGHT = 600;

    class Bexel {
        private:
            shared_ptr<Window> m_window;
            unique_ptr<GLShaderProgram> m_shader;

            unique_ptr<World> m_world;

        public:
            Bexel() : m_window(nullptr), m_shader(nullptr), m_world(nullptr) {

            }

            void init() {
                glfwInit();

                m_window = WindowFactory::create_window("3. OpenGL 3D cube example", GAME_WIDTH, GAME_HEIGHT, GfxAPI::OPENGL);

                gladLoadGL();
                glViewport(0, 0, GAME_WIDTH, GAME_HEIGHT);
                glfwSwapInterval(0);
            }

            void load() {
                auto vertexShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/3_opengl_3d_cube/vertex.shader", ShaderTypes::VERTEX_SHADER);
                auto fragmentShader = GLShaderFactory::create_shader("examples/assets/gfx/opengl/3_opengl_3d_cube/fragment.shader", ShaderTypes::FRAGMENT_SHADER);

                m_shader = make_unique<GLShaderProgram>(vertexShader, fragmentShader);
                m_world = make_unique<World>();
            }

            void run() {
                glEnable(GL_DEPTH_TEST);

                while (!m_window->closing()) {
                    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    m_world->render(m_shader);

                    glfwSwapBuffers(m_window->get_backend());
                    glfwPollEvents();
                }
            }

            void unload() {
                m_world = nullptr;

                m_shader->destroy();

                glfwTerminate();
            }
        };
}

#endif
