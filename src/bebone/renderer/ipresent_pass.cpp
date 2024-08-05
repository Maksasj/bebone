#include "ipresent_pass.h"

namespace bebone::renderer {
    IPresentPass::IPresentPass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IGraphicsPass(impl, pass_name, viewport) {
        register_input("texture", texture_attachment);
    }
}
