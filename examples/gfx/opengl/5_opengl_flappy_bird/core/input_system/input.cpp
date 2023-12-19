#include "input.h"

namespace game::core::input_system {
    map<MouseKeyCode, Action> Input::mouseActions = map<MouseKeyCode, Action>();
    queue<MouseKeyCode> Input::queuedMouseClicks = queue<MouseKeyCode>();

    void Input::register_mouse_action(const MouseKeyCode& keyCode, const Action& action) {
        mouseActions[keyCode] = action;
    }

    void Input::send_button_to_the_queue(const MouseKeyCode& keyCode) {
        queuedMouseClicks.push(keyCode);
    }

    void Input::execute_pooled_actions() {
        while (!queuedMouseClicks.empty()) {
            auto mouseKeyCode = queuedMouseClicks.front();
            queuedMouseClicks.pop();

            auto it = mouseActions.find(mouseKeyCode);
            if (it != mouseActions.end()) {
                (*it).second.execute();
            }
        }
    }
}