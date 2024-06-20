#include "input_handler.h"

namespace bebone::core {
    const KeyListener& InputHandler::get_key_listener() const {
        return key_listener;
    }

    const MouseListener& InputHandler::get_mouse_listener() const {
        return mouse_listener;
    }

    void InputHandler::execute_input_actions() const {
        Input::get_instance().execute_queued_actions();
    }
}