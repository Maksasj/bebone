#include "ipresent_pass.h"

namespace bebone::renderer {
    IPresentPass::IPresentPass(const std::string& pass_name) : IGraphicsPass(pass_name) {
        register_input("texture", texture_resource);
    }
}
