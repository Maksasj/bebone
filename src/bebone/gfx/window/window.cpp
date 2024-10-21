#include "window.h"

namespace bebone::gfx {
    Window::Window(const std::string& title, const int& width, const int& height, const WindowProperties& properties)
        : window_handler(this),
          width(width),
          height(height)
    {
        if(properties.enable_resize)
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

        add_listener(window_handler.get_window_size_listener());
    }

    Window::~Window() {
        glfwDestroyWindow(window);
        GLFWContext::terminate();// this should be moved somewhere else
    }

    void Window::pull_events() {
        GLFWContext::poll_events();
        fire(WindowPullEventsEvent());
    }

    void Window::glfw_window_pos_callback(GLFWwindow* glfw_window, int x_pos, int y_pos) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowPosEvent(x_pos, y_pos));
    }

    void Window::glfw_window_size_callback(GLFWwindow* glfw_window, int width, int height) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowSizeEvent(width, height));
    }

    void Window::glfw_window_close_callback(GLFWwindow* glfw_window) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowCloseEvent());
    }

    void Window::glfw_window_refresh_callback(GLFWwindow* glfw_window) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowRefreshEvent());
    }

    void Window::glfw_window_focus_callback(GLFWwindow* glfw_window, int focused) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowFocusEvent(focused));
    }

    void Window::glfw_window_iconify_callback(GLFWwindow* glfw_window, int iconified) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowIconifyEvent(iconified));
    }

    void Window::glfw_window_maximize_callback(GLFWwindow* glfw_window, int maximized) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowMaximizeEvent(maximized));
    }

    void Window::glfw_framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(FrameBufferSizeEvent(width, height));
    }

    void Window::glfw_window_content_scale_callback(GLFWwindow* glfw_window, float x_scale, float y_scale) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(WindowContentScaleEvent(x_scale, y_scale));
    }

    void Window::glfw_mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
        window->fire(InputMouseButtonEvent(button, action, mods));
    }

    void Window::glfw_key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods) {
        auto* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
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

    Vec2i Window::get_size() const {
        return Vec2i(width, height);
    }

    f32 Window::get_aspect() const {
        return static_cast<f32>(width) / static_cast<f32>(height);
    }

    const Watch& Window::get_watch() const {
        return watch;
    }

    void Window::end_frame() {
        double time_diff = watch.get_time_difference();
        Time::set_delta_time(time_diff);
        watch.update_timestamp();
    }
}
