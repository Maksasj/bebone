#include "bebone/bebone.h"

using namespace bebone::gfx;

int main() {
    RenderingEngine::preinit();

    Window window("Vulkan window", 800, 600);

    while (!window.closing()) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}