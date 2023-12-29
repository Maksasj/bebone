#ifndef _VOID_FUNCTION_H_
#define _VOID_FUNCTION_H_

#include <functional>

namespace bebone::core {
    class VoidFunction {
    private:
        std::function<void()> function;
    public:
        VoidFunction(const std::function<void()>& function);

        void execute();
    };
}

#endif