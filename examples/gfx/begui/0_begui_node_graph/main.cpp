#include "imgui_node_graph_test.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

int main() {
    auto window = WindowFactory::create_window("0. Begui Node graph example", screen_width, screen_height, OpenGL);

    window->add_listener([&](InputKeyEvent& event) {
        if(event.key == GLFW_KEY_ENTER && event.action == GLFW_RELEASE) {
            std::cout << "Called event !\n";
        }
    });

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);
    glfwSwapInterval(0);

    auto vertex_shader = GLShaderFactory::create_shader("vertex.glsl", ShaderType::VertexShader);
    auto fragment_shader = GLShaderFactory::create_shader("fragment.glsl", ShaderType::FragmentShader);
    GLShaderProgram shader_program(vertex_shader, fragment_shader);

    vertex_shader.destroy();
    fragment_shader.destroy();

    GLContext::enable(GL_DEPTH_TEST);

    BeGUI::init(window);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        BeGUI::begin();
            ShowExampleAppCustomNodeGraph(nullptr);
            ImGui::ShowDemoWindow();
        BeGUI::end();

        GLFWContext::swap_buffers(*window); // Todo make this not a reference
        window->pull_events();
    }

    shader_program.destroy();

    return 0;
}
