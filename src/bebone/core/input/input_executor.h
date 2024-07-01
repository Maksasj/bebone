#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "input.h"

#include <queue>

namespace bebone::core {
    // Queues input provided by the player and executes registered actions
    class InputExecutor {
        private:
            std::shared_ptr<Input> input;
            std::queue<Key> queued_keys;

        public:
            InputExecutor(const std::shared_ptr<Input>& input);

            [[nodiscard]] std::shared_ptr<Input> get_input() const;

            void queue_key(const KeyCode& key_code, const InputType& input_type);

            // Executes all queued input actions
            void execute_input_actions();
    };
}

#endif
