#include "irender_pass.h"

namespace bebone::renderer {
    IRenderPass::IRenderPass(const std::string& name) : name(name) {

    }

    const std::string& IRenderPass::get_name() const {
        return name;
    }
}
