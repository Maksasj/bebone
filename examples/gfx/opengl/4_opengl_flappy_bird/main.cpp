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

    Game game(SCR_WIDTH, SCR_HEIGHT);

    GLTexture texture("examples\\assets\\gfx\\opengl\\4_opengl_flappy_bird\\awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_UNSIGNED_BYTE);

    while (!window->closing()) {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        game.update(texture);

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
