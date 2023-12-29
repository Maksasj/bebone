#ifndef _WINDOW_EVENT_H_
#define _WINDOW_EVENT_H_

#include "../../../core/core.h"
#include "../../gfx_backend.h"

namespace bebone::gfx {
    using namespace core;

    class WindowEvent : public Event {
    public:
        GLFWwindow* window;

        WindowEvent(GLFWwindow* window);
        ~WindowEvent();
    };
}

#endif