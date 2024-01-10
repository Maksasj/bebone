#ifndef _KEY_H_
#define _KEY_H_

#include "key_code.h"
#include "input_type.h"

namespace bebone::core {
    struct Key {
        KeyCode keyCode;
        InputType inputType;

        Key(KeyCode keyCode, InputType inputType);
        bool operator==(const Key& other) const;
        bool operator<(const Key& other) const;
    };
}

#endif
