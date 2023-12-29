#include "window_event.h"

namespace bebone::gfx {
    WindowEvent::WindowEvent(GLFWwindow* window) : window(window) { }
    WindowEvent::~WindowEvent() {
        window = nullptr;
    }
}