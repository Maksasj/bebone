#ifndef _ACTION_H_
#define _ACTION_H_

#include <functional>

namespace game::core::input_system {
    class Action {
        private:
            std::function<void()> func;
        
        public:
            Action();
            Action(std::function<void()> func);

            void execute();
            void set_function(std::function<void()> func);
    };
}

#endif
