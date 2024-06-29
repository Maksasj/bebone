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

    /// Singleton Input System class. Works with Action delegates
    class Input {
        private:
            using BeboneAction = Action<>;

            map<Key, BeboneAction> key_actions;
            queue<Key> queued_keys;

            void queue_key(const KeyCode& key_code, const InputType& input_type);
            void execute_queued_actions();

        public:
            /*!
            * Registers the key to do specific action
            * 
            * @param key_code - key code
            * @param action - function object, which will execute when the key will be pressed/released
            * @param input_type - specifies the input type. By default it is set to InputType::PRESS
            */
            void register_key_action(const KeyCode& key_code, std::function<void()>& action, const InputType& input_type = InputType::Press);
            
            /*!
            * Removes the specific action from the key
            * 
            * @param key_code - key code
            * @param action - function object, which will execute when the key will be pressed/released
            * @param input_type - specifies the input type. By default it is set to InputType::PRESS
            */
            void remove_key_action(const KeyCode& key_code, std::function<void()>& action, const InputType& input_type = InputType::Press);

            friend class InputHandler;
            friend class KeyListener;
            friend class MouseListener;
    };
}

#endif