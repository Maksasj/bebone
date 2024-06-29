#include "input_handler.h"

namespace bebone::core {
    InputHandler::InputHandler() : input(std::make_shared<Input>()), key_listener(input), mouse_listener(input) {}

    const KeyListener& InputHandler::get_key_listener() const {
        return key_listener;
    }

    const MouseListener& InputHandler::get_mouse_listener() const {
        return mouse_listener;
    }

    void InputHandler::execute_input_actions() const {
        input->execute_queued_actions();
    }

    std::shared_ptr<Input> InputHandler::get_input() const {
        return input;
    }
}