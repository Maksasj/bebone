#include "opengl_window.h"

namespace bebone::gfx {
    GLWindow::GLWindow(const std::string& title, const int& width, const int& height) : Window(title, width, height) {
        glfwMakeContextCurrent(get_backend());
    }
}
