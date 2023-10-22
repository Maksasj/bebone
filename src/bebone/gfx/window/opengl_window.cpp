#include "opengl_window.h"

namespace bebone::gfx {
    GLWindow::GLWindow(const std::string& title, const int& width, const int& height) : Window(title, width, height) {
        GLFWwindow *window = get_backend();
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, window_resize_callback);

        glfwMakeContextCurrent(get_backend());
    }
}
