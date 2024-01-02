#include "input.h"

#include <utility>

namespace game::core::input_system {
    using Action = Action<>;

    map<MouseKeyCode, Action> Input::mouseActions = map<MouseKeyCode, Action>();
    queue<MouseKeyCode> Input::queuedMouseClicks = queue<MouseKeyCode>();

    void Input::register_mouse_action(const MouseKeyCode& keyCode, const shared_ptr<std::function<void()>>& function) {
        if (mouseActions.find(keyCode) == mouseActions.end()) {
            mouseActions[keyCode] = Action();
        }

        mouseActions[keyCode] += function;
    }

    void Input::send_button_to_the_queue(const MouseKeyCode& keyCode) {
        queuedMouseClicks.push(keyCode);
    }

    void Input::remove_mouse_action(const MouseKeyCode& keyCode, const shared_ptr<std::function<void()>>& function) {
        if (mouseActions.find(keyCode) == mouseActions.end()) {
            return;
        }

        mouseActions[keyCode] -= function;
    }

    void Input::execute_pooled_actions() {
        while (!queuedMouseClicks.empty()) {
            MouseKeyCode mouseKeyCode = queuedMouseClicks.front();
            queuedMouseClicks.pop();

            if (mouseActions.find(mouseKeyCode) != mouseActions.end()) {
                mouseActions[mouseKeyCode]();
            }
        }
    }
}