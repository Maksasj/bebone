#include "ipresent_pass.h"

namespace bebone::renderer {
    IPresentPass::IPresentPass(const std::string& pass_name, const Vec2i& viewport) : IGraphicsPass(pass_name, viewport) {
        register_input("texture", texture_resource);
    }
}
