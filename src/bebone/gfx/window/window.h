#ifndef _BEBONE_GFX_WINDOW_H_
#define _BEBONE_GFX_WINDOW_H_

#include <iostream>
#include <exception>

#include "../../core/core.h"

#include "../gfx_backend.h"

#include "events/window_event.h"

namespace bebone::gfx {
    using namespace core;

    class Window : private NonCopyable, public EventObserver<WindowEvent> {
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

            bool is_resized() const;
            bool closing() const;

            int get_width() const;
            int get_height() const;
            f32 get_aspect() const;
            GLFWwindow* get_backend() const;

            static void window_resize_callback(GLFWwindow* glfwWindow, int width, int height);
    };
}
#endif
