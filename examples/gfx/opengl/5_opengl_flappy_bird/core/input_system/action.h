#ifndef _ACTION_H_
#define _ACTION_H_

#include <functional>

namespace game::core::input_system {
    class Action {
        private:
            std::function<void()> func;

        public:
            Action(std::function<void()> func);
            void execute();
    };
}

#endif
