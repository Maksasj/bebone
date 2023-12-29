#ifndef _MOUSE_BUTTON_PRESS_EVENT_H_
#define _MOUSE_BUTTON_PRESS_EVENT_H_

#include "mouse_event.h"

namespace bebone::gfx {
    class MouseButtonPressEvent : MouseEvent {
    public:
        MouseButtonPressEvent(GLFWwindow* window) : MouseEvent(window) { }
    };
}

#endif