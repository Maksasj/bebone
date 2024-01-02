#include "window.h"

namespace bebone::gfx {
    Window::Window(const std::string& title, const int& width, const int& height) : width(width), height(height), windowResized(false) {
        window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        glfwSetWindowUserPointer(window, this);

        // Window callbacks
        glfwSetWindowPosCallback(window, glfw_window_pos_callback);
        glfwSetWindowSizeCallback(window, glfw_window_size_callback);
        glfwSetWindowCloseCallback(window, glfw_window_close_callback);
        glfwSetWindowRefreshCallback(window, glfw_window_refresh_callback);
        glfwSetWindowFocusCallback(window, glfw_window_focus_callback);
        glfwSetWindowIconifyCallback(window, glfw_window_iconify_callback);
        glfwSetWindowMaximizeCallback(window, glfw_window_maximize_callback);
        glfwSetFramebufferSizeCallback(window, glfw_framebuffer_size_callback);
        glfwSetWindowContentScaleCallback(window, glfw_window_content_scale_callback);

        // Mouse callbacks
        // glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }

    const bool& Window::is_resized() const {
        return windowResized;
    }

    void Window::reset_resize_flag() {
        windowResized = false;
    }

    void Window::glfw_window_pos_callback(GLFWwindow* glfwWindow, int xpos, int ypos) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowPosEvent());
    }

    void Window::glfw_window_size_callback(GLFWwindow* glfwWindow, int width, int height) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowSizeEvent());
    }

    void Window::glfw_window_close_callback(GLFWwindow* glfwWindow) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowCloseEvent());
    }

    void Window::glfw_window_refresh_callback(GLFWwindow* glfwWindow) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowRefreshEvent());
    }

    void Window::glfw_window_focus_callback(GLFWwindow* glfwWindow, int focused) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowFocusEvent());
    }

    void Window::glfw_window_iconify_callback(GLFWwindow* glfwWindow, int iconified) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowIconifyEvent());
    }

    void Window::glfw_window_maximize_callback(GLFWwindow* glfwWindow, int maximized) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowMaximizeEvent());
    }

    void Window::glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(FrameBufferSizeEvent());
    }

    void Window::glfw_window_content_scale_callback(GLFWwindow* glfwWindow, float xscale, float yscale) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        eventDispatcher->fire(WindowContentScaleEvent());
    }

    /*
    void Window::glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods) {
        auto* eventDispatcher = reinterpret_cast<EventDispatcher<WindowEvent>*>(glfwGetWindowUserPointer(glfwWindow));
        // Todo there we need to fire necessary events
        eventDispatcher->fire(MousePressEvent());
    }
    */

    GLFWwindow* Window::get_backend() const {
        return window;
    }

    bool Window::closing() const {
        return glfwWindowShouldClose(window);
    }

    const int& Window::get_width() const {
        return width;
    }

    const int& Window::get_height() const {
        return height;
    }

    f32 Window::get_aspect() const {
        return static_cast<f32>(width) / static_cast<f32>(height);
    }
}
