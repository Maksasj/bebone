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

        if (key_input_types.find(key_code) == key_input_types.end()) {
            key_input_types[key_code] = InputType::None;
        }
    }

    void InputExecutor::execute_input_actions() {
        convert_released_keys_to_none();

        while (!queued_keys.empty()) {
            const auto key = queued_keys.front();
            KeyCode key_code = key.key_code;
            InputType input_type = key.input_type;

            queued_keys.pop();

            if (input_type == InputType::Press || input_type == InputType::Repeat) {
                pressed_keys[key_code] = true;
            } else {
                pressed_keys[key_code] = false;
                released_keys.push_back(key_code);
            }

            key_input_types[key_code] = input_type;

            input->apply_action(key);
        }
    }

    void InputExecutor::convert_released_keys_to_none() {
        for (auto& released_key : released_keys) {
            key_input_types[released_key] = InputType::None;
        }

        released_keys.clear();
    }

    bool InputExecutor::is_key_down(const KeyCode& key_code) {
        if (key_input_types.find(key_code) == key_input_types.end()) {
            return false;
        }

        return pressed_keys[key_code];
    }

    bool InputExecutor::is_key_up(const KeyCode& key_code) {
        return !is_key_down(key_code);
    }

    bool InputExecutor::is_key_pressed(const KeyCode& key_code) {
        if (key_input_types.find(key_code) == key_input_types.end()) {
            return false;
        }

        return pressed_keys[key_code] && key_input_types[key_code] == InputType::Press;
    }

    bool InputExecutor::is_key_released(const KeyCode& key_code) {
        if (key_input_types.find(key_code) == key_input_types.end()) {
            return false;
        }

        return !pressed_keys[key_code] && key_input_types[key_code] == InputType::Release;
    }
}