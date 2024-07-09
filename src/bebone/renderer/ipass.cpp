#include "ipass.h"

namespace bebone::renderer {
    IPass::IPass(const std::string& name) : name(name) {

    }

    const std::string& IPass::get_name() const {
        return name;
    }
}
