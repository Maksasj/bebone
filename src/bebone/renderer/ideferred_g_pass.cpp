#include "ideferred_g_pass.h"

namespace bebone::renderer {
    using namespace bebone::core;

    IDeferredGPass::IDeferredGPass(
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IRenderQueuePass(pass_name, viewport) {
        register_output("position", position_resource);
        register_output("normals", normals_resource);
        register_output("albedo", albedo_resource);
        register_output("specular", specular_resource);

        register_output("depth", depth_resource);
    }
}
