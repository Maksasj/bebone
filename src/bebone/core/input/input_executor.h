#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "input.h"
#include "key_listener.h"
#include "mouse_listener.h"

#include <queue>

namespace bebone::core {
    // Queues input provided by the player and executes registered actions
    class InputExecutor {
        private:
            std::shared_ptr<Input> input;
            std::queue<Key> queued_keys;
            KeyListener key_listener;
            MouseListener mouse_listener;

        public:
            InputExecutor();

            // Getter for key listener
            [[nodiscard]] const KeyListener& get_key_listener() const;

            // Getter for mouse listener
            [[nodiscard]] const MouseListener& get_mouse_listener() const;

            [[nodiscard]] std::shared_ptr<Input> get_input() const;

            void queue_key(const KeyCode& key_code, const InputType& input_type);

            // Executes all input actions
            void execute_input_actions();
    };
}

#endif
