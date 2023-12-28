#ifndef _VULKAN_WINDOW_H_
#define _VULKAN_WINDOW_H_

#include "window.h"

namespace bebone::gfx {
    class VulkanWindow : public Window {
        public:
            VulkanWindow(const std::string& title, const int& width, const int& height);

            void create_window_surface(VkInstance instance, VkSurfaceKHR *surface);
    };
}

#endif
