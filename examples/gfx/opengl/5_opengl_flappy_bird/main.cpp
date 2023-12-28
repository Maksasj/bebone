#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "core/game.h"
#include "core/sprite.h"
#include "core/game_time.h"

#include "core/input_system/input.h"

const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 800;

using namespace bebone::core;
using namespace bebone::gfx;

using namespace game::core;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    using namespace input_system;
    std::ignore = window;
    std::ignore = mods;

    if (action == GLFW_PRESS) {
        auto mouseKeyCode = static_cast<MouseKeyCode>(button);
        Input::send_button_to_the_queue(mouseKeyCode);
    }
}

int main() {
    glfwInit();
    
    auto window = WindowFactory::create_window("5. Flappy bird", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
    glfwSwapInterval(1);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    Game game(SCR_WIDTH, SCR_HEIGHT);

    glfwSetMouseButtonCallback(window->get_backend(), mouse_button_callback);
    double beginTime = Time::get_time();
    double endTime;

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (Time::deltaTime >= 0) {
            game.update();
        }

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();

        endTime = Time::get_time();
        Time::deltaTime = endTime - beginTime;
        beginTime = endTime;
    }
    
    glfwTerminate();
    return 0;
}
