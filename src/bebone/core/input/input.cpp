#include "input.h"

namespace bebone::core {
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

    void Input::apply_action(const Key& key) {
        if (key_actions.find(key) != key_actions.end()) {
            key_actions[key]();
        }
    }
}