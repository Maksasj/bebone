#ifndef _KEY_H_
#define _KEY_H_

#include "key_code.h"
#include "input_type.h"

namespace bebone::core {
    /// Key data type, which holds the key code and input type
    struct Key {
        KeyCode keyCode;
        InputType inputType;

        Key(KeyCode keyCode, InputType inputType);
        bool operator==(const Key& other) const;
        bool operator<(const Key& other) const;
    };
}

#endif
