#ifndef _INPUT_H_
#define _INPUT_H_

#include <map>
#include <queue>
#include <memory>

#include "bebone/bebone.h"

#include "key_codes.h"

namespace game::core::input_system {
    using namespace bebone::core;
    using namespace std;

    class Input {
        private:
            static map<MouseKeyCode, shared_ptr<Action>> mouseActions;
            static queue<MouseKeyCode> queuedMouseClicks;

        public:
            static void register_mouse_action(const MouseKeyCode& keyCode, const shared_ptr<VoidFunction>& function);
            static void remove_mouse_action(const MouseKeyCode& keyCode, const shared_ptr<VoidFunction>& function);
            static void send_button_to_the_queue(const MouseKeyCode& keyCode);
            static void execute_pooled_actions();
    };
}

#endif
