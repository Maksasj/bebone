#include "bebone/bebone.h"

#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    glfwInit();

    Window window("Window example", SCR_WIDTH, SCR_HEIGHT, GfxAPI::OPENGL);

    gladLoadGL();
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    while (!window.closing())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window.get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
