#include "window.h"

namespace bebone::gfx {
    Window::Window(const std::string& title, const int width, const int height, const GfxAPI& gfxAPI) : _width(width), _height(height) {
        windowResized = false;

        if (gfxAPI == GfxAPI::VULKAN) {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

            _window = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);
            glfwSetWindowUserPointer(_window, this);
            glfwSetFramebufferSizeCallback(_window, window_resize_callback);
        } else {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            _window = glfwCreateWindow(_width, _height, title.c_str(), NULL, NULL);
            glfwMakeContextCurrent(_window);
        }

        if (_window == NULL) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }
    }

    Window::~Window() {
        glfwDestroyWindow(_window);
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
        window->_width = width;
        window->_height = height;
    }

    GLFWwindow* Window::get_backend() const {
        return _window;
    }

    bool Window::closing() const {
        return glfwWindowShouldClose(_window);
    }

    VkExtent2D Window::get_extend() const {
        return { static_cast<uint32_t>(_width), static_cast<uint32_t>(_height) };
    }

    int Window::get_width() const {
        return _width;
    }

    int Window::get_height() const {
        return _height;
    }

    f32 Window::get_aspect() const {
        return static_cast<f32>(_width) / static_cast<f32>(_height);
    }

    void Window::create_window_surface(VkInstance instance, VkSurfaceKHR *surface_) {
        if(glfwCreateWindowSurface(instance, _window, nullptr, surface_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface");
        }
    }
}
