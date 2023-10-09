#include "window.h"

namespace bebone::gfx {
    Window::Window(const std::string& title, const int& width, const int& height) : width(width), height(height), windowResized(false) {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }

    bool Window::is_resized() {
        return windowResized;
    }

    void Window::reset_resize_flag() {
        windowResized = false;
    }

    void Window::window_resize_callback(GLFWwindow* glfwWindow, int width, int height) {
        Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->windowResized = true;
        window->width = width;
        window->height = height;
    }

    GLFWwindow* Window::get_backend() const {
        return window;
    }

    bool Window::closing() const {
        return glfwWindowShouldClose(window);
    }

    int Window::get_width() const {
        return width;
    }

    int Window::get_height() const {
        return height;
    }

    f32 Window::get_aspect() const {
        return static_cast<f32>(width) / static_cast<f32>(height);
    }
}
