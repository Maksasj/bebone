#include "window_handler.h"
#include "window.h"

namespace bebone::gfx {
    WindowHandler::WindowHandler(Window* window) : window_size_listener(window) {

    }

    const WindowSizeListener& WindowHandler::get_window_size_listener() const {
        return window_size_listener;
    }
}
