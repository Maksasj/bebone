#ifndef _INPUT_QUEUE_H
#define _INPUT_QUEUE_H

#include <queue>

#include "key.h"
#include "key_code.h"

namespace bebone::core {
    class InputQueue {
    private:
        std::queue<Key> queued_keys;

    public:
        void queue_key(const KeyCode& key_code, const InputType& input_type);
        Key pop_key();
    };
}

#endif
