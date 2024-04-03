#ifndef _BEBONE_GFX_WINDOW_WINDOW_SIZE_LISTENER_H_
#define _BEBONE_GFX_WINDOW_WINDOW_SIZE_LISTENER_H_

#include <memory>
#include <string>

#include "events/window_event.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    class Window;

    class WindowSizeListener : EventListener<WindowSizeEvent> {
        private:
            Window* window;

        public:
            WindowSizeListener(Window* win);

            void operator()(WindowSizeEvent& event);
    };
}

#endif
