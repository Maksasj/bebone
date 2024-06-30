#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "input.h"

#include <queue>
#include <map>

namespace bebone::core {
    // Queues input provided by the player and executes registered actions
    class InputExecutor {
        private:
            std::shared_ptr<Input> input;
            std::queue<Key> queued_keys;
            std::map<KeyCode, int> pressed_keys_count;

        public:
            InputExecutor(const std::shared_ptr<Input>& input);

            [[nodiscard]] std::shared_ptr<Input> get_input() const;

            void queue_key(const KeyCode& key_code, const InputType& input_type);

            // Executes all queued input actions
            void execute_input_actions();

            bool is_key_pressed(const KeyCode& key_code);
            bool is_key_down(const KeyCode& key_code);
            bool is_key_up(const KeyCode& key_code);
    };
}

#endif
