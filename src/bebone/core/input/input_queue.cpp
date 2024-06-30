#include "input_queue.h"

namespace bebone::core {
    void InputQueue::queue_key(const KeyCode &key_code, const InputType &input_type) {
        queued_keys.emplace(key_code, input_type);
    }

    Key InputQueue::pop_key() {
        Key key = Key();

        if (!queued_keys.empty()) {
            key = queued_keys.front();
            queued_keys.pop();
        }

        return key;
    }
}