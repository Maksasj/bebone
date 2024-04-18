#ifndef _BEBONE_GFX_WINDOW_WINDOW_SIZE_LISTENER_H_
#define _BEBONE_GFX_WINDOW_WINDOW_SIZE_LISTENER_H_

#include <memory>
#include <string>

#include "events/window_event.h"

#include "../gfx_backend.h"

namespace bebone::gfx {
    class Window;

    // Window resize listener class
    class WindowSizeListener : EventListener<WindowSizeEvent> {
        private:
            Window* window;

        public:
            /*!
            * Default constructor
            * @param win - pointer to window
            */
            WindowSizeListener(Window* win);

            /*!
            * Event execution method
            * @param event - event object
            */
            void operator()(WindowSizeEvent& event) override;
    };
}

#endif
