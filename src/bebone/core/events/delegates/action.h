#ifndef _ACTION_H_
#define _ACTION_H_

#include <memory>
#include <vector>

#include "void_function.h"

namespace bebone::core {
    using namespace std;

    class Action {
    private:
        vector<shared_ptr<VoidFunction>> functions;
    public:
        Action();

        void subscribe(shared_ptr<VoidFunction> function);
        void unsubscribe(shared_ptr<VoidFunction> function);
        void invoke();
    };
}

#endif