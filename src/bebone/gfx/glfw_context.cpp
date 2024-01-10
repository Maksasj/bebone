#include "glfw_context.h"

namespace bebone::gfx {
    void GLFWContext::init() {
        glfwInit();
    }

    void GLFWContext::make_context_current(const Window& window) {
        glfwMakeContextCurrent(window.get_backend());
    }

    void GLFWContext::swap_buffers(const Window& window) {
        glfwSwapBuffers(window.get_backend());
    }

    void GLFWContext::poll_events() {
        glfwPollEvents();
    }

    void GLFWContext::terminate() {
        glfwTerminate();
    }
}
