#include "input_executor.h"

namespace bebone::core {
    InputExecutor::InputExecutor() : input(std::make_shared<Input>()) { }

    std::shared_ptr<Input> InputExecutor::get_input() const {
        return input;
    }

    void InputExecutor::queue_key(const KeyCode &key_code, const InputType &input_type) {
        queued_keys.emplace(key_code, input_type);
    }

    void InputExecutor::execute_input_actions() {
        while (!queued_keys.empty()) {
            const auto key = queued_keys.front();

            queued_keys.pop();

            input->apply_action(key);
        }
    }
}