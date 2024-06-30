#define BEBONE_TYPES_MATRIX_COLUMN_MAJOR_ORDER
#define BEBONE_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "core/game.h"
#include "core/game_time.h"

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

    InputHandler input_handler = InputHandler();

    window->add_listener(input_handler.get_key_listener());
    window->add_listener(input_handler.get_mouse_listener());

    Game game(screen_width, screen_height, input_handler.get_input());

    double begin_time = Time::get_time();
    double end_time;

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        input_handler.execute_input_actions();

        if (Time::delta_time >= 0) {
            game.update();
        }

        glfwSwapBuffers(window->get_backend());
        GLFWContext::poll_events();

        end_time = Time::get_time();
        Time::delta_time = end_time - begin_time;
        begin_time = end_time;
    }
    
    GLFWContext::terminate();
    return 0;
}
