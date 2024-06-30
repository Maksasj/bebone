#include "input_executor.h"

namespace bebone::core {
    InputExecutor::InputExecutor(const std::shared_ptr<Input>& input) : input(input) { }

    std::shared_ptr<Input> InputExecutor::get_input() const {
        return input;
    }

    void InputExecutor::queue_key(const KeyCode &key_code, const InputType &input_type) {
        queued_keys.emplace(key_code, input_type);

        if (pressed_keys.find(key_code) == pressed_keys.end()) {
            pressed_keys[key_code] = false;
        }
    }

    void InputExecutor::execute_input_actions() {
        while (!queued_keys.empty()) {
            const auto key = queued_keys.front();

            queued_keys.pop();

            if (key.input_type == InputType::Press || key.input_type == InputType::Repeat) {
                pressed_keys[key.key_code] = true;
            } else {
                pressed_keys[key.key_code] = false;
            }

            input->apply_action(key);
        }
    }

    bool InputExecutor::is_key_down(const KeyCode& key_code) {
        return pressed_keys[key_code];
    }

    bool InputExecutor::is_key_up(const KeyCode& key_code) {
        return !is_key_down(key_code);
    }
}