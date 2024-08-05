#include "irender_queue_pass.h"

namespace bebone::renderer {
    IRenderQueuePass::IRenderQueuePass(
        const std::shared_ptr<IPassImpl>& impl,
        const std::string& pass_name,
        const Vec2i& viewport
    ) : IGraphicsPass(impl, pass_name, viewport) {

    }
}
