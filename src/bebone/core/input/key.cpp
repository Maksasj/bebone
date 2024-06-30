#include "key.h"

namespace bebone::core {
    Key::Key() : key_code(KeyCode::Null), input_type(InputType::Null) { }

    Key::Key(KeyCode key_code, InputType input_type) : key_code(key_code), input_type(input_type) { }

    bool Key::operator==(const Key& other) const {
        return key_code == other.key_code && input_type == other.input_type;
    }

    bool Key::operator<(const bebone::core::Key &other) const {
        return key_code < other.key_code;
    }
}