#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("0. Input example", screen_width, screen_height, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    std::function<void()> key_press = []() {
        std::cout << "key press\n";
    };

    InputHandler input_handler = InputHandler();
    window->add_listener(input_handler.get_key_listener());
    window->add_listener(input_handler.get_mouse_listener());

    auto input = input_handler.get_input();
    input->register_key_action(KeyCode::A, key_press);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        input_handler.execute_input_actions();

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
