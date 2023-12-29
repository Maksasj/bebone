#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::gfx::vulkan;

int main() {
    RenderingEngine::preinit();

    auto window = WindowFactory::create_window("0. Vulkan window example", 800, 600, GfxAPI::VULKAN);

    while (!window->closing()) {
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}