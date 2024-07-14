#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("0. Vulkan window example", 800, 600, Vulkan);

    while (!window->closing()) {
        window->pull_events();
    }

    GLFWContext::terminate();

    return 0;
}