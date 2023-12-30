#ifndef _ACTION_H_
#define _ACTION_H_

#include <memory>
#include <vector>
#include <functional>

namespace bebone::core {
    template <typename... Args>
    class Action {
        using Function = std::shared_ptr<std::function<void(Args...)>>;

    private:
        std::vector<Function> functions;
    public:
        Action() : functions(std::vector<Function>()) { };

        void operator+=(const Function& function) {
            functions.push_back(function);
        }

        void operator-=(const Function& function) {
            auto it = std::find(functions.begin(), functions.end(), function);

            if (it != functions.end()) {
                functions.erase(it);
            }
        }

        void operator()(Args... args) const {
            for (const auto& function : functions) {
                (*function)(args...);
            }
        }
    };
}

#endif