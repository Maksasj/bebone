#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;

int main() {
    GLFWContext::init();
    
    auto window = WindowFactory::create_window("0. OpenGL window example", screen_width, screen_height, GfxAPI::OpenGL);

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        GLFWContext::swap_buffers(*window);
        GLFWContext::poll_events();
    }

    GLFWContext::terminate();
    return 0;
}
