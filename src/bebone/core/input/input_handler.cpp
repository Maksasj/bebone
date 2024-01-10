#include "input_handler.h"

namespace bebone::core {
    const KeyListener& InputHandler::get_key_listener() const {
        return keyListener;
    }

    const MouseListener& InputHandler::get_mouse_listener() const {
        return mouseListener;
    }

    void InputHandler::execute_input_actions() const {
        Input::get_instance().execute_queued_actions();
    }
}