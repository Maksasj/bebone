#include "imgui_node_graph_test.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

int main() {
    BEBONE_PROFILE_RECORD(MAIN)

    GLFWContext::init();

    auto window = WindowFactory::create_window("0. Begui Node graph example", screen_width, screen_height, OpenGL);

    window->add_listener([&](InputKeyEvent& event) {
        if(event.key == GLFW_KEY_ENTER && event.action == GLFW_RELEASE) {
            BEBONE_PROFILE_RECORD(EVENT)

            std::cout << "Called event !\n";

            BEBONE_PROFILE_STOP(EVENT)
        }
    });

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);
    glfwSwapInterval(0);

    auto vertex_shader = GLShaderFactory::create_shader("vertex.glsl", VertexShader);
    auto fragment_shader = GLShaderFactory::create_shader("fragment.glsl", FragmentShader);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);

    vertex_shader.destroy();
    fragment_shader.destroy();

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
        window->pull_events();

        BEBONE_PROFILE_STOP(LOOP)
    }

    shader_program.destroy();

    GLFWContext::terminate();

    BEBONE_PROFILE_STOP(MAIN)
    std::cout << BEBONE_PROFILER_SUM_UP() << "\n";

    return 0;
}
