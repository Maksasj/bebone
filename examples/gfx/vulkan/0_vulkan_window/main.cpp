#include "bebone/bebone.h"

using namespace bebone::gfx;

int main() {
    GLFWContext::init();

    auto window = WindowFactory::create_window("0. Vulkan window example", 800, 600, GfxAPI::VULKAN);

    while (!window->closing()) {
        GLFWContext::pool_events();
    }

    GLFWContext::terminate();

    return 0;
}