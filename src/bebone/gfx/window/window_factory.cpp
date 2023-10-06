#include "window_factory.h"
#include "opengl_window.h"
#include "vulkan_window.h"

namespace bebone::gfx {
    std::shared_ptr<Window> WindowFactory::create_window(const std::string& title, const int width, const int height, const GfxAPI& gfxAPI) {
        std::shared_ptr<Window> window;

        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

        if (gfxAPI == GfxAPI::OPENGL) {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            window = std::make_shared<GLWindow>(title, width, height);
        } else {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
            
            window = std::make_shared<VulkanWindow>(title, width, height);
        }

        if (window->get_backend() == NULL) {
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        return window;
    }
}
