#ifndef _MOUSE_EVENT_H_
#define _MOUSE_EVENT_H_

#include "window_event.h"

namespace bebone::gfx {
    class MouseEvent : WindowEvent {
    public:
        MouseEvent(GLFWwindow* window) : WindowEvent(window) { }
    };
}

#endif