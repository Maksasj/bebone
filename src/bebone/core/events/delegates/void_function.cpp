#include "void_function.h"

namespace bebone::core {
    VoidFunction::VoidFunction(const std::function<void()> &function) : function(function) { }

    void VoidFunction::execute() {
        function();
    }
}