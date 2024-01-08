#ifndef _INPUT_H_
#define _INPUT_H_

#include <map>
#include <queue>

#include "../events/delegates/action.h"

#include "input_type.h"
#include "key_code.h"
#include "key.h"

namespace bebone::core {
    using namespace std;

    class Input {
        using Action = Action<>;

    private:
        map<Key, Action> keyActions;
        queue<Key> queuedKeys;

        Input() {}

        void queue_key(const KeyCode& keyCode, const InputType& inputType);
        void execute_queued_actions();

        // TODO: friend class (for example, window will queue the keys using callbacks and will execute queued keys before draw calls)
    public:
        Input(const Input& obj) = delete;
        void operator=(Input const& obj) = delete;

        static Input& get_instance();

        void register_key_action(const KeyCode& keyCode, std::function<void()>& action, const InputType& inputType = InputType::PRESS);
        void remove_key_action(const KeyCode& keyCode, std::function<void()>& action, const InputType& inputType = InputType::PRESS);
    };
}

#endif