#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "input.h"
#include "key_listener.h"
#include "mouse_listener.h"

namespace bebone::core {
    // Input handler class
    class InputHandler {
        private:
            KeyListener keyListener;
            MouseListener mouseListener;

        public:
            // Getter for key listener
            const KeyListener& get_key_listener() const;

            // Getter for mouse listener
            const MouseListener& get_mouse_listener() const;

            // Executes all input actions
            void execute_input_actions() const;
    };
}

#endif
