#ifndef _MOUSE_LISTENER_H_
#define _MOUSE_LISTENER_H_

#include "../events/listeners/event_listener.tpp"

#include "../../gfx/window/events/input_event.h"

#include "input.h"

namespace bebone::core {
    using namespace gfx;

    struct MouseListener : EventListener<InputMouseButtonEvent> {
        void operator()(InputMouseButtonEvent& event) override {
            Input& input = Input::get_instance();

            KeyCode key_code = static_cast<KeyCode>(event.button);
            InputType input_type = static_cast<InputType>(event.action);
            input.queue_key(key_code, input_type);
        }
    };
}

#endif
