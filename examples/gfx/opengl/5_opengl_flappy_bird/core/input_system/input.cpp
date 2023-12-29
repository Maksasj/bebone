#include "input.h"

#include <utility>

namespace game::core::input_system {
    map<MouseKeyCode, shared_ptr<Action>> Input::mouseActions = map<MouseKeyCode, shared_ptr<Action>>();
    queue<MouseKeyCode> Input::queuedMouseClicks = queue<MouseKeyCode>();

    void Input::register_mouse_action(const MouseKeyCode& keyCode, const shared_ptr<VoidFunction>& function) {
        if (mouseActions[keyCode] == nullptr) {
            mouseActions[keyCode] = make_shared<Action>();
        }

        auto action = mouseActions[keyCode];

        if (action != nullptr) {
            action->subscribe(function);
        }
    }

    void Input::send_button_to_the_queue(const MouseKeyCode& keyCode) {
        queuedMouseClicks.push(keyCode);
    }

    void Input::remove_mouse_action(const MouseKeyCode& keyCode, const shared_ptr<VoidFunction>& function) {
        auto action = mouseActions[keyCode];

        if (action == nullptr) {
            return;
        }

        action->unsubscribe(function);
    }

    void Input::execute_pooled_actions() {
        while (!queuedMouseClicks.empty()) {
            MouseKeyCode mouseKeyCode = queuedMouseClicks.front();
            queuedMouseClicks.pop();

            auto action = mouseActions[mouseKeyCode];

            if (action != nullptr) {
                action->invoke();
            }
        }
    }
}