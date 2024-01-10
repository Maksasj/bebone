#ifndef _ACTION_H_
#define _ACTION_H_

#include <memory>
#include <vector>
#include <functional>

namespace bebone::core {
    /// Action delegate. Similar to the C# Action. Can subscribe/unsubscribe functions and execute them
    /// @tparam ...Args function argument types
    template <typename... Args>
    class Action {
        using Function = std::function<void(Args...)>;

    private:
        std::vector<Function*> functions;
    public:
        Action() : functions(std::vector<Function*>()) { };

        /*!
        * Subscribes function object to the action delegate
        *
        * @param function - function object
        */
        void operator+=(Function& function) {
            functions.push_back(&function);
        }

        /*!
        * Unsubscribes function object from the action
        *
        * @param function - function object
        */
        void operator-=(Function& function) {
            auto it = std::find(functions.begin(), functions.end(), &function);

            if (it != functions.end()) {
                functions.erase(it);
            }
        }

        /*!
        * Executes all subscribed functions
        *  
        * @param args - function arguments
        */
        void operator()(Args... args) const {
            for (const auto& function : functions) {
                (*function)(args...);
            }
        }
    };
}

#endif