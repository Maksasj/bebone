#include "mouse_listener.h"

namespace bebone::gfx {
    MouseListener::MouseListener(std::shared_ptr<InputExecutor>& input_executor) : input_executor(input_executor) { }

    void MouseListener::operator()(InputMouseButtonEvent &event) {
        const auto key_code = static_cast<KeyCode>(event.button);
        const auto input_type = static_cast<InputType>(event.action);
        input_executor->queue_key(key_code, input_type);
    }
}