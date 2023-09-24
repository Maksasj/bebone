#include "bebone/bebone.h"

using namespace bebone::gfx;

int main() {
    RenderingEngine::preinit();

    Window window("0. Vulkan window example", 800, 600);

    while (!window.closing()) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}