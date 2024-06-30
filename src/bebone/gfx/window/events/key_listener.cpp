#include "key_listener.h"

namespace bebone::gfx {
    KeyListener::KeyListener(std::shared_ptr<InputExecutor>& input_executor) : input_executor(input_executor) {}

    void KeyListener::operator()(gfx::InputKeyEvent &event) {
        const auto key_code = static_cast<KeyCode>(event.key);
        const auto input_type = static_cast<InputType>(event.action);
        input_executor->queue_key(key_code, input_type);
    }
}