#include "ideferred_g_pass.h"

namespace bebone::renderer {
    using namespace bebone::core;

    IDeferredGPass::IDeferredGPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IRenderQueuePass(impl, pass_name, viewport) {
        register_output("position", position_attachment);
        register_output("normals", normals_attachment);
        register_output("albedo", albedo_attachment);
        register_output("specular", specular_attachment);

        register_output("depth", depth_attachment);
    }
}
