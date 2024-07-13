#ifndef _BEBONE_GFX_WINDOW_WINDOW_H_
#define _BEBONE_GFX_WINDOW_WINDOW_H_

#include <iostream>
#include <exception>

#include "../gfx_backend.h"
#include "../gfx_api.h"

#include "events/window_event.h"
#include "events/input_event.h"

#include "window_properties.h"
#include "window_handler.h"

#include "../../core/timestamp/timestamp.h"
#include "../../core/timestamp/watch.h"

namespace bebone::renderer {
    class IRenderer;
}

namespace bebone::gfx {
    using namespace core;

    /// Abstract window class
    class Window : private NonCopyable, public EventDispatcher<WindowEvent>, public EventDispatcher<InputEvent> {
        private:
            GLFWwindow* window;

            WindowHandler window_handler;

            Watch watch;

        protected:
            int width;
            int height;

            friend class WindowSizeListener;

        public:
            using EventDispatcher<WindowEvent>::add_listener;
            using EventDispatcher<WindowEvent>::fire;

            using EventDispatcher<InputEvent>::add_listener;
            using EventDispatcher<InputEvent>::fire;

            /*!
             * Default abstract window constructor
             * @param title - desired window title
             * @param width - window width
             * @param height - window height
            */
            Window(const std::string& title, const int& width, const int& height, const WindowProperties& properties = {});
            ~Window();

            /*!
             * Function that checks does window want to close
             * @return - boolean value is window closing
            */
            bool closing() const;

            /// Function that returns window width
            const int& get_width() const;

            /// Function that returns window height
            const int& get_height() const;

            Vec2i get_size() const;

            /// Function that returns current window aspect ration
            f32 get_aspect() const;

            /// Function returns glfw window backend
            GLFWwindow* get_backend() const;

            /// Gfx api
            virtual GfxAPI get_api() const = 0;

            const Watch& get_watch() const;

            void end_frame();

        private:
            /// GLFW window position change callbacks
            static void glfw_window_pos_callback(GLFWwindow* glfw_window, int x_pos, int y_pos);
            /// GLFW window size change callbacks
            static void glfw_window_size_callback(GLFWwindow* glfw_window, int width, int height);
            /// GLFW window close callback
            static void glfw_window_close_callback(GLFWwindow* handle);
            /// GLFW window refresh callback
            static void glfw_window_refresh_callback(GLFWwindow* handle);
            /// GLFW window focus callback
            static void glfw_window_focus_callback(GLFWwindow* handle, int focused);
            /// GLFW window iconify callback
            static void glfw_window_iconify_callback(GLFWwindow* handle, int iconified);
            /// GLFW window maximize callback
            static void glfw_window_maximize_callback(GLFWwindow* handle, int maximized);
            /// GLFW window framebuffer size callback
            static void glfw_framebuffer_size_callback(GLFWwindow* glfw_window, int width, int height);
            /// GLFW window content scale callback
            static void glfw_window_content_scale_callback(GLFWwindow* handle, float x_scale, float y_scale);

            /// GLFW mouse button press callback
            static void glfw_mouse_button_callback(GLFWwindow* glfw_window, int button, int action, int mods);
            /// GLFW key press callback
            static void glfw_key_callback(GLFWwindow* glfw_window, int key, int scancode, int action, int mods);

    };
}
#endif
