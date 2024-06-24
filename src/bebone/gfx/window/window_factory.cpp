#include "window_factory.h"
#include "opengl_window.h"
#include "vulkan_window.h"

#include "../glfw_context.h"

namespace bebone::gfx {
    std::shared_ptr<Window> WindowFactory::create_window(const std::string& title, const int& width, const int& height, const GfxAPI& gfx_api, const WindowProperties& properties) {
        std::shared_ptr<Window> window;

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        if (gfx_api == GfxAPI::OPENGL) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = std::make_shared<GLWindow>(title, width, height, properties);
        } else {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            
            window = std::make_shared<VulkanWindow>(title, width, height, properties);
        }

        if (window->get_backend() == nullptr) {
            GLFWContext::terminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        return window;
    }
}
