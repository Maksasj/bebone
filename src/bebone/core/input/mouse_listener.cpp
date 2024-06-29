#include "mouse_listener.h"

namespace bebone::core {
    MouseListener::MouseListener(std::shared_ptr<Input>& input) : input(input) { }

    void MouseListener::operator()(InputMouseButtonEvent &event) {
        const auto key_code = static_cast<KeyCode>(event.button);
        const auto input_type = static_cast<InputType>(event.action);
        input->queue_key(key_code, input_type);
    }
}