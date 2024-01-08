#include "input.h"

namespace bebone::core {
    Input& Input::get_instance() {
        static Input instance;

        return instance;
    }

    void Input::register_key_action(const KeyCode& keyCode, std::function<void()>& action, const InputType& inputType) {
        Key key(keyCode, inputType);

        if (keyActions.find(key) == keyActions.end()) {
            keyActions[key] = Action();
        }

        keyActions[key] += action;
    }

    void Input::remove_key_action(const bebone::core::KeyCode &keyCode, std::function<void()> &action, const bebone::core::InputType &inputType) {
        Key key(keyCode, inputType);

        if (keyActions.find(key) == keyActions.end()) {
            return;
        }

        keyActions[key] -= action;
    }

    void Input::queue_key(const bebone::core::KeyCode &keyCode, const bebone::core::InputType &inputType) {
        queuedKeys.push(Key(keyCode, inputType));
    }

    void Input::execute_queued_actions() {
        while (!queuedKeys.empty()) {
            Key key = queuedKeys.front();
            queuedKeys.pop();

            if (keyActions.find(key) != keyActions.end()) {
                keyActions[key]();
            }
        }
    }
}