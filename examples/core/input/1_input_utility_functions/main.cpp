#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("1. Input utility functions example", screen_width, screen_height, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    auto input = std::make_shared<Input>();
    auto input_executor = std::make_shared<InputExecutor>(input);

    KeyListener key_listener = KeyListener(input_executor);
    window->add_listener(key_listener);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        if (input_executor->is_key_down(KeyCode::A)) {
            std::cout << "key A is down\n";
        }

        // if (input_executor->is_key_up(KeyCode::A)) {
        //     std::cout << "key A is up\n";
        // }

        if (input_executor->is_key_pressed(KeyCode::A)) {
            std::cout << "key A is pressed\n";
        }

        input_executor->execute_input_actions();

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
