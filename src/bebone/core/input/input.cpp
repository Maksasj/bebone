#include "input.h"

namespace bebone::core {
    Input& Input::get_instance() {
        static Input instance;

        return instance;
    }

    void Input::register_key_action(const KeyCode& key_code, std::function<void()>& action, const InputType& input_type) {
        const Key key(key_code, input_type);

        if (key_actions.find(key) == key_actions.end()) {
            key_actions[key] = Action();
        }

        key_actions[key] += action;
    }

    void Input::remove_key_action(const KeyCode &key_code, std::function<void()> &action, const InputType &input_type) {
        const Key key(key_code, input_type);

        if (key_actions.find(key) == key_actions.end()) {
            return;
        }

        key_actions[key] -= action;
    }

    void Input::queue_key(const KeyCode &key_code, const InputType &input_type) {
        queued_keys.emplace(key_code, input_type);
    }

    void Input::execute_queued_actions() {
        while (!queued_keys.empty()) {
            const auto key = queued_keys.front();

            queued_keys.pop();

            if (key_actions.find(key) != key_actions.end()) {
                key_actions[key]();
            }
        }
    }
}