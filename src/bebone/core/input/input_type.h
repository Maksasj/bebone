#ifndef _INPUT_TYPE_H_
#define _INPUT_TYPE_H_

namespace bebone::core {
    /// Specifies in which case the action will be executed
    enum class InputType {
        Press,
        Release,
        Null
    };
}

#endif