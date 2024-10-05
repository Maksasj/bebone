#ifndef BEBONE_GLFW_CONTEXT_H
#define BEBONE_GLFW_CONTEXT_H

#include <iostream>

#include "window/window.h"

namespace bebone::gfx {
    class Window;

    /// GLFW library wrapper
    class GLFWContext {
        public:
            /// Initializes the GLFW
            static void init();

            /*!
             * glfwMakeContextCurrent function
             * @param window - window object
             */
            static void make_context_current(const Window& window);

            /*!
             * glfwSwapBuffers function
             * @param window - window object
             */
            static void swap_buffers(const Window& window);

            /// glfwPollEvents function
            static void poll_events();

            /// Terminates the GLFW
            static void terminate();
    };
}

#endif
