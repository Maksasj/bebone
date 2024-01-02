#ifndef _INPUT_H_
#define _INPUT_H_

#include <map>
#include <queue>

#include "../events/delegates/action.h"

#include "input_type.h"
#include "key_code.h"

namespace bebone::core {
    using namespace std;

    class Input {
        using Action = Action<>;

    private:
        map<KeyCode, Action> keyActions;
        queue<KeyCode> queuedKeys;

    public:
        void register_key_action(const KeyCode& keyCode, std::function<void()>& action, const InputType& inputType = InputType::PRESS);
        void remove_key_action(const KeyCode& keyCode, std::function<void()>& action, const InputType& inputType = InputType::PRESS);
        void send_key_to_the_queue(const KeyCode& keyCode);
        void execute_pooled_actions();
    };
}

#endif