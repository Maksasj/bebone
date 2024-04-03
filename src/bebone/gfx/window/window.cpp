#include "window.h"

namespace bebone::gfx {
    Window::Window(const std::string& title, const int& width, const int& height, const WindowProperties& properties)
        : windowHandler(this),
          width(width),
          height(height)
    {
        if(properties.enableResize)
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        else
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

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
        glfwSetMouseButtonCallback(window, glfw_mouse_button_callback);
        glfwSetKeyCallback(window, glfw_key_callback);

        add_listener(inputHandler.get_key_listener());
        add_listener(inputHandler.get_mouse_listener());

        add_listener(windowHandler.get_window_size_listener());
    }

    Window::~Window() {
        glfwDestroyWindow(window);
    }

    void Window::glfw_window_pos_callback(GLFWwindow* glfwWindow, int xPos, int yPos) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowPosEvent(xPos, yPos));
    }

    void Window::glfw_window_size_callback(GLFWwindow* glfwWindow, int width, int height) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowSizeEvent(width, height));
    }

    void Window::glfw_window_close_callback(GLFWwindow* glfwWindow) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowCloseEvent());
    }

    void Window::glfw_window_refresh_callback(GLFWwindow* glfwWindow) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowRefreshEvent());
    }

    void Window::glfw_window_focus_callback(GLFWwindow* glfwWindow, int focused) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowFocusEvent(focused));
    }

    void Window::glfw_window_iconify_callback(GLFWwindow* glfwWindow, int iconified) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowIconifyEvent(iconified));
    }

    void Window::glfw_window_maximize_callback(GLFWwindow* glfwWindow, int maximized) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowMaximizeEvent(maximized));
    }

    void Window::glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(FrameBufferSizeEvent(width, height));
    }

    void Window::glfw_window_content_scale_callback(GLFWwindow* glfwWindow, float xscale, float yscale) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(WindowContentScaleEvent(xscale, yscale));
    }

    void Window::glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(InputMouseButtonEvent(button, action, mods));
    }

    void Window::glfw_key_callback(GLFWwindow* glfwWindow, int key, int scancode, int action, int mods) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfwWindow));
        window->fire(InputKeyEvent(key, scancode, action, mods));
    }

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

    void Window::execute_input_actions() const {
        inputHandler.execute_input_actions();
    }
}
