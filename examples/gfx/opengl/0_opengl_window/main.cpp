#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

int main() {
    LOG_TRACE("Test message");
    LOG_DEBUG("Test message");
    LOG_INFORMATION("Test message");
    LOG_WARNING("Test message");
    LOG_ERROR("Test message");
    LOG_CRITICAL("Test message");

    auto window = WindowFactory::create_window("0. OpenGL window example", screen_width, screen_height, OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        GLFWContext::swap_buffers(*window);
        window->pull_events();
    }

    return 0;
}
