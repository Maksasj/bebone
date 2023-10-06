#include "vulkan_window.h"

namespace bebone::gfx {
    VulkanWindow::VulkanWindow(const std::string& title, const int width, const int height) : Window(title, width, height) {
        GLFWwindow *window = get_backend();
        glfwSetWindowUserPointer(window, this);
        glfwSetFramebufferSizeCallback(window, window_resize_callback);
    }

    void VulkanWindow::create_window_surface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, get_backend(), nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface");
        }
    }

    VkExtent2D VulkanWindow::get_extend() const {
        return { static_cast<uint32_t>(get_width()), static_cast<uint32_t>(get_height()) };
    }
}
