#ifndef _KEY_LISTENER_H_
#define _KEY_LISTENER_H_

#include "../events/listeners/event_listener.tpp"

#include "../../gfx/window/events/input_event.h"

#include "input.h"

#include <iostream>

namespace bebone::core {
    using namespace gfx;

    struct KeyListener : EventListener<InputKeyEvent> {
        void operator()(InputKeyEvent& event) {
            Input& input = Input::get_instance();

            KeyCode keyCode = static_cast<KeyCode>(event.key);
            InputType inputType = static_cast<InputType>(event.action);
            input.queue_key(keyCode, inputType);
        }
    };
}

#endif
