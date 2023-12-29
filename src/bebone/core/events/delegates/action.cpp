#include "action.h"

namespace bebone::core {
    Action::Action() : functions(vector<shared_ptr<VoidFunction>>()) { }

    void Action::subscribe(const shared_ptr<VoidFunction>& function) {
        functions.push_back(function);
    }

    void Action::unsubscribe(const shared_ptr<VoidFunction>& function) {
        auto it = find(functions.begin(), functions.end(), function);

        if (it != functions.end()) {
            functions.erase(it);
        }
    }

    void Action::invoke() {
        for (const auto& function : functions) {
            function->execute();
        }
    }
}