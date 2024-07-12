#include "ideferred_g_pass.h"

namespace bebone::renderer {
    using namespace bebone::core;

    IDeferredGPass::IDeferredGPass(
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IRenderQueuePass(pass_name, viewport) {
        register_output("texture", texture_resource);
        register_output("depth", depth_resource);
    }
}
