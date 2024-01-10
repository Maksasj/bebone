#include "key.h"

namespace bebone::core {
    Key::Key(KeyCode keyCode, InputType inputType) : keyCode(keyCode), inputType(inputType) { }

    bool Key::operator==(const Key& other) const {
        return keyCode == other.keyCode && inputType == other.inputType;
    }

    bool Key::operator<(const bebone::core::Key &other) const {
        return keyCode < other.keyCode;
    }
}