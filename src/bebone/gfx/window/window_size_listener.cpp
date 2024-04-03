#include "window_size_listener.h"
#include "window.h"

namespace bebone::gfx {
    WindowSizeListener::WindowSizeListener(Window* win) : window(win) {

    }

    void WindowSizeListener::operator()(WindowSizeEvent& event) {
        window->width = event.width;
        window->height = event.height;
    }
}
