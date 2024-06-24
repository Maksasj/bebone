#include "bebone/bebone.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("0. Input example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    std::function<void()> key_press = []() {
        std::cout << "key press\n";
    };

    Input::get_instance().register_key_action(KeyCode::A, key_press);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        window->execute_input_actions();

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
