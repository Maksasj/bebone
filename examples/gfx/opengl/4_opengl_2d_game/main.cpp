#define OMNI_TYPES_MATRIX_COLLUM_MAJOR_ORDER
#define OMNI_TYPES_MATRIX4X4_PROJECTION_MATRIX_INVERSE_Y_AXIS
#include "bebone/bebone.h"

#include "core/game.h"

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

using namespace bebone::core;
using namespace bebone::gfx;

using namespace game::core;

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("4. 2d game example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    gladLoadGL();
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    Game game;

    while (!window->closing()) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.update();

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
