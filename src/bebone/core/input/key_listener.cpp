#include "key_listener.h"

namespace bebone::core {
    KeyListener::KeyListener(std::shared_ptr<Input> &input) : input(input) {}

    void KeyListener::operator()(gfx::InputKeyEvent &event) {
        const auto key_code = static_cast<KeyCode>(event.key);
        const auto input_type = static_cast<InputType>(event.action);
        input->queue_key(key_code, input_type);
    }
}