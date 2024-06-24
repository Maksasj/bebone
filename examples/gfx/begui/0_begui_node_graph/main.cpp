#include "imgui_node_graph_test.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

int main() {
    BEBONE_PROFILE_RECORD(MAIN)

    GLFWContext::init();

    auto window = WindowFactory::create_window("0. Begui Node graph example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    window->add_listener([&](InputKeyEvent& event) {
        if(event.key == GLFW_KEY_ENTER && event.action == GLFW_RELEASE) {
            BEBONE_PROFILE_RECORD(EVENT)

            std::cout << "Called event !\n";

            BEBONE_PROFILE_STOP(EVENT)
        }
    });

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSwapInterval(0);

    auto vertexShader = GLShaderFactory::create_shader("vertex.glsl", ShaderTypes::vertex_shader);
    auto fragmentShader = GLShaderFactory::create_shader("fragment.glsl", ShaderTypes::fragment_shader);
    GLShaderProgram shaderProgram(vertexShader, fragmentShader);

    vertexShader.destroy();
    fragmentShader.destroy();

    GLContext::enable(GL_DEPTH_TEST);

    BeGUI::init(window);

    while (!window->closing()) {
        BEBONE_PROFILE_RECORD(LOOP)

        BEBONE_PROFILE_RECORD(CLEAR)
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        BEBONE_PROFILE_STOP(CLEAR)

        BEBONE_PROFILE_RECORD(BEGUI)
        BeGUI::begin();
            ShowExampleAppCustomNodeGraph(nullptr);
            ImGui::ShowDemoWindow();
            BeGUI::show_profiler();
        BeGUI::end();
        BEBONE_PROFILE_STOP(BEGUI)

        GLFWContext::swap_buffers(*window); // Todo make this not a reference
        GLFWContext::poll_events();

        BEBONE_PROFILE_STOP(LOOP)
    }

    shaderProgram.destroy();

    GLFWContext::terminate();

    BEBONE_PROFILE_STOP(MAIN)
    std::cout << BEBONE_PROFILER_SUM_UP() << "\n";

    return 0;
}
