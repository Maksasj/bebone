#ifndef _BEBONE_GFX_WINDOW_VULKAN_WINDOW_H_
#define _BEBONE_GFX_WINDOW_VULKAN_WINDOW_H_

#include "window.h"

namespace bebone::gfx {
    /// The class implements a window specifically for Vulkan graphics api
    class VulkanWindow : public Window {
        public:
            /*!
             * Default constructor
             * @param title - desired window title
             * @param width - desired window width
             * @param height - desired window height
            */
            VulkanWindow(const std::string& title, const int& width, const int& height, const WindowProperties& properties = {});

            /*!
             * Function that creates window surface for this window
             * @param instance - Vulkan instance
             * @param surface - pointer to vulkan surface
            */
            void create_window_surface(VkInstance instance, VkSurfaceKHR *surface);

            GfxAPI get_api() const override;
    };
}

#endif
