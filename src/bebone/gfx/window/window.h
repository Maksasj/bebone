#ifndef _BEBONE_GFX_WINDOW_H_
#define _BEBONE_GFX_WINDOW_H_

#include <iostream>
#include <exception>

#include "../../core/core.h"

#include "../gfx_backend.h"

#include "events/window_event.h"

namespace bebone::gfx {
    using namespace core;



    class Window : private NonCopyable, public EventDispatcher<WindowEvent> {
        private:
            GLFWwindow* window;
            int width;
            int height;

        public:
            Window(const std::string& title, const int& width, const int& height);
            ~Window();
            
            bool closing() const;

            const int& get_width() const;
            const int& get_height() const;
            f32 get_aspect() const;
            GLFWwindow* get_backend() const;

        private:
            // Window callbacks
            static void glfw_window_pos_callback(GLFWwindow* glfwWindow, int xPos, int yPos);
            static void glfw_window_size_callback(GLFWwindow* glfwWindow, int width, int height);
            static void glfw_window_close_callback(GLFWwindow* handle);
            static void glfw_window_refresh_callback(GLFWwindow* handle);
            static void glfw_window_focus_callback(GLFWwindow* handle, int focused);
            static void glfw_window_iconify_callback(GLFWwindow* handle, int iconified);
            static void glfw_window_maximize_callback(GLFWwindow* handle, int maximized);
            static void glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
            static void glfw_window_content_scale_callback(GLFWwindow* handle, float xScale, float yScale);

            // Mouse callbacks
            // static void glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods);

    };
}
#endif
