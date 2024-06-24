#include "bebone/bebone.h"

const unsigned int screen_width = 800;
const unsigned int screen_height = 600;

using namespace bebone::gfx;
using namespace bebone::gfx::opengl;

void window_resize_event_listener(WindowSizeEvent&) {
    std::cout << "Window resize event !\n";
}

struct WindowPosEventListener : EventListener<WindowPosEvent> {
    void operator()(WindowPosEvent&) {
        std::cout << "Window pos event !\n";
    }
};

int main() {
    glfwInit();

    auto window = WindowFactory::create_window("0. OpenGL window example", screen_width, screen_height, GfxAPI::OPENGL);

    WindowPosEventListener listener;
    window->add_listener(listener);

    window->add_listener(listener);
    window->add_listener(window_resize_event_listener);
    window->add_listener([](WindowFocusEvent&) {
        std::cout << "Window focus event !\n";
    });

    window->fire(WindowPosEvent(0, 0));

    GLContext::load_opengl();
    GLContext::set_viewport(0, 0, screen_width, screen_height);

    while (!window->closing()) {
        GLContext::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        GLContext::clear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window->get_backend());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
