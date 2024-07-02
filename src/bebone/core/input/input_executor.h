#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "input.h"

#include <queue>
#include <map>
#include <vector>

namespace bebone::core {
    // Queues input provided by the player and executes registered actions
    class InputExecutor {
        private:
            std::shared_ptr<Input> input;
            std::queue<Key> queued_keys;

            std::map<KeyCode, bool> pressed_keys;
            std::map<KeyCode, InputType> key_input_types;
            std::vector<KeyCode> released_keys;

            void convert_released_keys_to_none();

        public:
            InputExecutor(const std::shared_ptr<Input>& input);

            [[nodiscard]] std::shared_ptr<Input> get_input() const;

            void queue_key(const KeyCode& key_code, const InputType& input_type);

            // Executes all queued input actions
            void execute_input_actions();

            bool is_key_down(const KeyCode& key_code);
            bool is_key_up(const KeyCode& key_code);
            bool is_key_pressed(const KeyCode& key_code);
            bool is_key_released(const KeyCode& key_code);
    };
}

#endif
