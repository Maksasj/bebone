#include "input_executor.h"

namespace bebone::core {
    InputExecutor::InputExecutor(const std::shared_ptr<Input>& input) : input(input) { }

    std::shared_ptr<Input> InputExecutor::get_input() const {
        return input;
    }

    void InputExecutor::queue_key(const KeyCode &key_code, const InputType &input_type) {
        queued_keys.emplace(key_code, input_type);

        if (pressed_keys_count.find(key_code) == pressed_keys_count.end()) {
            pressed_keys_count[key_code] = 0;
        }

        ++pressed_keys_count[key_code];
    }

    void InputExecutor::execute_input_actions() {
        while (!queued_keys.empty()) {
            const auto key = queued_keys.front();

            queued_keys.pop();
            --pressed_keys_count[key.key_code];

            input->apply_action(key);
        }
    }

    bool InputExecutor::is_key_down(const KeyCode& key_code) {
        if (pressed_keys_count.find(key_code) == pressed_keys_count.end()) {
            return false;
        }

        if (pressed_keys_count[key_code] > 0) {
            return true;
        }

        return false;
    }

    bool InputExecutor::is_key_up(const KeyCode& key_code) {
        return !is_key_down(key_code);
    }

    bool InputExecutor::is_key_pressed(const KeyCode& key_code) {
        if (pressed_keys_count.find(key_code) == pressed_keys_count.end()) {
            return false;
        }

        if (pressed_keys_count[key_code] == 1) {
            return true;
        }

        return false;
    }
}