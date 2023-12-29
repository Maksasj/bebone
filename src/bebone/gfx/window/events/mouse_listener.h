#ifndef _MOUSE_LISTENER_H_
#define _MOUSE_LISTENER_H_

#include "mouse_button_press_event.h"

namespace bebone::gfx {
    class MouseListener : EventListener<MouseEvent> {
        void handle_event(shared_ptr<MouseEvent> event) override;
    };
}

#endif