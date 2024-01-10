#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "input.h"
#include "key_listener.h"
#include "mouse_listener.h"

namespace bebone::core {
    class InputHandler {
    private:
        KeyListener keyListener;
        MouseListener mouseListener;
    public:
        const KeyListener& get_key_listener() const;
        const MouseListener& get_mouse_listener() const;

        void execute_input_actions() const;
    };
}

#endif
