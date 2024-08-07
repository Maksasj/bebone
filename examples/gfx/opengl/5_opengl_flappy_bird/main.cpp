#include "bebone/bebone.h"

#include "core/game.h"

const unsigned int screen_width = 600;
const unsigned int screen_height = 800;

using namespace bebone::core;
using namespace bebone::gfx;

using namespace game::core;

int main() {
    glfwInit();
    
    auto window = WindowFactory::create_window("5. Flappy Bird", screen_width, screen_height, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    auto input = std::make_shared<Input>();
    auto input_executor = std::make_shared<InputExecutor>(input);

    KeyListener key_listener(input_executor);
    MouseListener mouse_listener(input_executor);

    window->add_listener(key_listener);
    window->add_listener(mouse_listener);

    Game game(screen_width, screen_height, input);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input_executor->execute_input_actions();

        game.update();

        glfwSwapBuffers(window->get_backend());
        GLFWContext::poll_events();

        window->end_frame();
    }
    
    GLFWContext::terminate();
    return 0;
}
