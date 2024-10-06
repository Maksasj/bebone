#include "window_factory.h"
#include "opengl_window.h"
#include "vulkan_window.h"

#include "../glfw_context.h"

namespace bebone::gfx {
    std::unique_ptr<Window> WindowFactory::create_window(const std::string& title, const int& width, const int& height, const GfxAPI& gfx_api, const WindowProperties& properties) {
        GLFWContext::init(); // this should be moved somewhere else
        LOG_TRACE("Initializing window {} {} with title: '{}'", width, height, title);

        std::unique_ptr<Window> window;

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        if (gfx_api == OpenGL) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = std::make_unique<GLWindow>(title, width, height, properties);
        } else {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            
            window = std::make_unique<VulkanWindow>(title, width, height, properties);
        }

        if (window->get_backend() == nullptr) {
            GLFWContext::terminate();
            LOG_ERROR("Failed to create GLFW window");
            throw std::runtime_error("Failed to create GLFW window");
        }

        return window;
    }
}
