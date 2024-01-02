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

            // Lets maybe implement this in some sort of bit flag and funstion should be like get_window_flags();
            bool windowResized;

        public:
            Window(const std::string& title, const int& width, const int& height);
            ~Window();
            
            void reset_resize_flag();

            const bool& is_resized() const;
            bool closing() const;

            const int& get_width() const;
            const int& get_height() const;
            f32 get_aspect() const;
            GLFWwindow* get_backend() const;

        private:
            // Window callbacks
            static void glfw_window_pos_callback(GLFWwindow* glfwWindow, int xpos, int ypos);
            static void glfw_window_size_callback(GLFWwindow* glfwWindow, int width, int height);
            static void glfw_window_close_callback(GLFWwindow* handle);
            static void glfw_window_refresh_callback(GLFWwindow* handle);
            static void glfw_window_focus_callback(GLFWwindow* handle, int focused);
            static void glfw_window_iconify_callback(GLFWwindow* handle, int iconified);
            static void glfw_window_maximize_callback(GLFWwindow* handle, int maximized);
            static void glfw_framebuffer_size_callback(GLFWwindow* glfwWindow, int width, int height);
            static void glfw_window_content_scale_callback(GLFWwindow* handle, float xscale, float yscale);

            // Mouse callbacks
            // static void glfw_mouse_button_callback(GLFWwindow* glfwWindow, int button, int action, int mods);

    };
}
#endif
