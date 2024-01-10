#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "core/game.h"
#include "core/game_time.h"

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 800;

using namespace bebone::core;
using namespace bebone::gfx;

using namespace game::core;

int main() {
    glfwInit();
    
    auto window = WindowFactory::create_window("5. Flappy Bird", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Game game(SCR_WIDTH, SCR_HEIGHT);

    double beginTime = Time::get_time();
    double endTime;

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        window->execute_input_actions();

        if (Time::deltaTime >= 0) {
            game.update();
        }

        glfwSwapBuffers(window->get_backend());
        GLFWContext::pool_events();

        endTime = Time::get_time();
        Time::deltaTime = endTime - beginTime;
        beginTime = endTime;
    }
    
    GLFWContext::terminate();
    return 0;
}
