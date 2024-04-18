#include "window_handler.h"
#include "window.h"

namespace bebone::gfx {
    WindowHandler::WindowHandler(Window* window) : windowSizeListener(window) {

    }

    const WindowSizeListener& WindowHandler::get_window_size_listener() const {
        return windowSizeListener;
    }
}
