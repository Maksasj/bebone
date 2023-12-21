#ifndef _INPUT_H_
#define _INPUT_H_

#include <map>
#include <queue>

#include "key_codes.h"
#include "action.h"

namespace game::core::input_system {
    using namespace std;

    class Input {
        private:
            static map<MouseKeyCode, Action> mouseActions;
            static queue<MouseKeyCode> queuedMouseClicks;

        public:
            static void register_mouse_action(const MouseKeyCode& keyCode, const Action& action);
            static void remove_mouse_action(const MouseKeyCode& keyCode);
            static void send_button_to_the_queue(const MouseKeyCode& keyCode);
            static void execute_pooled_actions();
    };
}

#endif
