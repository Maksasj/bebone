#include "bebone/bebone.h"

using namespace bebone::core;
using namespace bebone::gfx;
using namespace bebone::gfx::vulkan;

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("0. Vulkan window example", 800, 600, GfxAPI::Vulkan);

    while (!window->closing()) {
        GLFWContext::poll_events();
    }

    GLFWContext::terminate();

    return 0;
}