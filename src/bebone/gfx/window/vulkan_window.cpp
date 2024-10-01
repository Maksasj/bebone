#include "vulkan_window.h"

namespace bebone::gfx {
    VulkanWindow::VulkanWindow(const std::string& title, const int& width, const int& height, const WindowProperties& properties) : Window(title, width, height, properties) {
        LOG_TRACE("Initialized Vulkan window");
    }

    void VulkanWindow::create_window_surface(VkInstance instance, VkSurfaceKHR *surface) {
        if (glfwCreateWindowSurface(instance, get_backend(), nullptr, surface) != VK_SUCCESS)
            throw std::runtime_error("failed to create window surface");
    }

    GfxAPI VulkanWindow::get_api() const {
        return GfxAPI::Vulkan;
    }
}
