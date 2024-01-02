#ifndef BEBONE_GLFW_CONTEXT_H
#define BEBONE_GLFW_CONTEXT_H

#include <iostream>

#include "gfx_backend.h"
#include "window/window.h"

namespace bebone::gfx {
    class GLFWContext {
    public:
        static void init();

        static void make_context_current(const Window& window);

        static void swap_buffers(const Window& window);

        static void pool_events();

        static void terminate();
    };
}

#endif
