#include "vulkan_window.h"

namespace bebone::gfx {
    VulkanWindow::VulkanWindow(const std::string& title, const int& width, const int& height) : Window(title, width, height) {

    }

    void VulkanWindow::create_window_surface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, get_backend(), nullptr, surface) != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface");
        }
    }
}
